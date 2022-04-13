# これはなに
aexはAfterEffectsSDKの代替を目指すSDKです
まだまだ不完全です

# つかいかた
`PiPLTool`だけはどうしようもなかったので本家SDKは準備してください

- `aex.zip`を好きなフォルダに展開する
- `aex`以下に本家SDKの`Resources`フォルダをコピー

ここからはプロジェクトの作り方 (VS)
- インクルードパスに`aex.zipを展開したフォルダ`を追加する
- プロジェクトに`pipl.r`，`pipl.rc`ファイルを追加する
- `pipl.r`のプロパティを変更していく
  -  項目の種類を`カスタム ビルド ツール`にする 
  - コマンドラインを↓にする
```
cl /I "<aex>" /EP "%(Filename).r" > "$(IntDir)%(Filename).rr" & "<aex>\aex\Resources\PiPLTool" "$(SolutionDir)$(IntDir)%(Filename).rr" "$(SolutionDir)$(IntDir)%(Filename).rrc" & cl /D "MSWindows" /EP "$(IntDir)%(Filename).rrc" > "%(Filename).rc"
```
    - `<aex>`の部分は`aex.zipを展開したフォルダ`のパスにしてください
  - 出力ファイルを↓にする
```
$(ProjectDir)%(Filename).rc;%(Outputs)
```

- `pipl.rc`のプロパティを変更していく
  - 項目の種類が`リソース コンパイラ`になっているのを確認
  - 構成`Debug`で`リソース > プリプロセッサの定義`に`_DEBUG`を追加

で、コードは
```cpp
#include <aex_effect.hpp>
class MyEffect : public Effect {
public:
	template<class... T>
	MyEffect(T... args) : Effect(args...) {}
} effect("name", "match_name", "category", "EffectMain");

extern "C" PF_Err __declspec(dllexport) EffectMain(PF_Cmd cmd, PF_InData* in_data, PF_OutData* out_data, PF_ParamDef* params[], PF_LayerDef* output) {
	return effect.Main(cmd, in_data, out_data, params, output);
}

extern "C" __declspec(dllexport) PF_Err PluginDataEntryFunction(PF_PluginDataPtr inPtr,PF_PluginDataCB inPluginDataCallBackPtr,SPBasicSuite* inSPBasicSuitePtr,const char* inHostName,const char* inHostVersion) {
	return effect.Entry(inPtr, inPluginDataCallBackPtr);
}
```
みたいに書く想定です 不完全なのでこれじゃだめかも

例(Skeleton)
```cpp
#include <memory>
#include <format>

#define NOMINMAX
#include <Windows.h>

#define AEX_USE_CPPEXCEPTION

#include <aex_effect.hpp>

using namespace aex;

class MyEffect : public Effect {
public:
	template<class... T> MyEffect(T... args) : Effect(args...) {}

	PF_Err GlobalSetUp() noexcept override {
		out_data->my_version = PF_Version(1, 0, 0, 0, 1);
		out_data->out_flags = PF_OutFlags::DeepColorAware;
		return PF_Err::None;
	}

	PF_Err ParamsSetUp() noexcept override try {
		int id = 1;
		AddFloatSliderX("gain", 0, 100, 0, 100, 10, PF_Precision::Hundredths, 0, PF_ParamFlags::None, id++);
		AddColor("color", 128, 255, 255, id++);
		out_data->num_params = id;
		return PF_Err::None;
	}
	catch (const pf_exception& e) {
		return e.code();
	}

	struct GainInfo {
		PF_FpLong gainF;
	};

	template<class Pixel>
	static PF_Err Iterateor(void* refcon, A_long xL, A_long yL, Pixel* inP, Pixel* outP) {
		auto giP = reinterpret_cast<GainInfo*>(refcon);
		if (giP) {
			PF_FpLong tempF = std::min<PF_FpLong>(giP->gainF * std::numeric_limits<decltype(outP->red)>::max(), std::numeric_limits<decltype(outP->red)>::max());
			outP->alpha = inP->alpha;
			outP->red   = std::min<decltype(outP->red)>(inP->red   + tempF, std::numeric_limits<decltype(outP->red)>::max());
			outP->green = std::min<decltype(outP->red)>(inP->green + tempF, std::numeric_limits<decltype(outP->red)>::max());
			outP->blue  = std::min<decltype(outP->red)>(inP->blue  + tempF, std::numeric_limits<decltype(outP->red)>::max());
		}
		return PF_Err::None;
	}
	

	PF_Err Render() noexcept override try {
		AEGP_SuiteHandler suites(in_data->pica_basicP);
		GainInfo giP{};
		A_long linesL = output->extent_hint.bottom - output->extent_hint.top;
		giP.gainF = params[1]->u.fs_d.value * .01;
		if (has_flag(output->world_flags, PF_WorldFlags::Deep)) {
			AEX_PF_ERR_CHECK(suites.Iterate16Suite1()->iterate(in_data, 0, linesL, &params[0]->u.ld, NULL, &giP, &Iterateor<PF_Pixel16>, output));
		}
		else {
			AEX_PF_ERR_CHECK(suites.Iterate8Suite1()->iterate(in_data, 0, linesL, &params[0]->u.ld, NULL, &giP, &Iterateor<PF_Pixel>, output));
		};
		return PF_Err::None;
	}
	catch (const pf_exception& e) {
		return e.code();
	}
};

MyEffect effect("Skeleton", "ePi Skeleton", "ePi", "EffectMain");

extern "C" PF_Err __declspec(dllexport) EffectMain(PF_Cmd cmd, PF_InData* in_data, PF_OutData* out_data, PF_ParamDef* params[], PF_LayerDef* output) {
	return effect.Main(cmd, in_data, out_data, params, output);
}

extern "C" __declspec(dllexport) PF_Err PluginDataEntryFunction(PF_PluginDataPtr inPtr, PF_PluginDataCB inPluginDataCallBackPtr, SPBasicSuite * inSPBasicSuitePtr, const char* inHostName, const char* inHostVersion) {
	return effect.Entry(inPtr, inPluginDataCallBackPtr);
}
```

## ライセンス
1条項BSD
詳細は LICENSE を見ること
