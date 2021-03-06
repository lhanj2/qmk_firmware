# `info.json`

<!---
  original document: 0.10.33:docs/reference_info_json.md
  git diff 0.10.33 HEAD -- docs/reference_info_json.md | cat
-->

このファイルは [QMK API](https://github.com/qmk/qmk_api) によって使われます。このファイルは [QMK Configurator](https://config.qmk.fm/) がキーボードの画像を表示するために必要な情報を含んでいます。ここにメタデータを設定することもできます。

このメタデータを指定するために、`qmk_firmware/keyboards/<name>` の下の全てのレベルで `info.json` を作成することができます。これらのファイルは結合され、より具体的なファイルがそうではないファイルのキーを上書きします。つまり、メタデータ情報を複製する必要はありません。例えば、`qmk_firmware/keyboards/clueboard/info.json` は `manufacturer` および `maintainer` を指定し、`qmk_firmware/keyboards/clueboard/66/info.json` は Clueboard 66% についてのより具体的な情報を指定します。

## `info.json` の形式

`info.json` ファイルは設定可能な以下のキーを持つ JSON 形式の辞書です。全てを設定する必要はなく、キーボードに適用するキーだけを設定します。

* `keyboard_name`
   * キーボードを説明する自由形式のテキスト文字列。
   * 例: `Clueboard 66%`
* `url`
   * キーボードの製品ページ、[QMK.fm/keyboards](https://qmk.fm/keyboards) のページ、あるいはキーボードに関する情報を説明する他のページの URL。
* `maintainer`
   * メンテナの GitHub のユーザ名、あるいはコミュニティが管理するキーボードの場合は `qmk`
* `layouts`
   * 物理的なレイアウト表現。詳細は以下のセクションを見てください。

### レイアウトの形式

`info.json` ファイル内の辞書の `layouts` 部分は、幾つかの入れ子になった辞書を含みます。外側のレイヤーは QMK レイアウトマクロで構成されます。例えば、`LAYOUT_ansi` あるいは `LAYOUT_iso`。各レイアウトマクロ内には、`width`、 `height`、`key_count` のキーがあります。これらは自明でなければなりません。

* `width`
   * オプション: キー単位でのレイアウトの幅
* `height`
   * オプション: キー単位でのレイアウトの高さ
* `key_count`
   * オプション: このレイアウトのキーの数
* `layout`
   * 物理レイアウトを説明するキー辞書のリスト。詳細は次のセクションを見てください。

### キー辞書形式

レイアウトの各キー辞書は、キーの物理プロパティを記述します。<https://keyboard-layout-editor.com> の Raw Code に精通している場合、多くの概念が同じであることが分かります。可能な限り同じキー名とレイアウトの選択を再利用しますが、keyboard-layout-editor とは異なって各キーはステートレスで、前のキーからプロパティを継承しません。

全てのキーの位置と回転は、キーボードの左上と、各キーの左上を基準にして指定されます。

* `x`
   * **必須**: 水平軸でのキーの絶対位置(キー単位)。
* `y`
   * **必須**: 垂直軸でのキーの絶対位置(キー単位)。
* `w`
   * キー単位でのキーの幅。`ks` が指定された場合は無視されます。デフォルト: `1`
* `h`
   * キー単位でのキーの高さ。`ks` が指定された場合は無視されます。デフォルト: `1`
* `r`
   * キーを回転させる時計回りの角度。
* `rx`
   * キーを回転させる点の水平軸における絶対位置。デフォルト: `x`
* `ry`
   * キーを回転させる点の垂直軸における絶対位置。デフォルト: `y`
* `ks`
   * キー形状: キー単位で頂点を列挙することでポリゴンを定義します。
   * **重要**: これらはキーの左上からの相対位置で、絶対位置ではありません。
   * ISO Enter の例: `[ [0,0], [1.5,0], [1.5,2], [0.25,2], [0.25,1], [0,1], [0,0] ]`
* `label`
   * マトリックス内のこの位置につける名前。
   * これは通常 PCB 上でこの位置にシルクスクリーン印刷されるものと同じ名前でなければなりません。

## メタデータはどのように公開されますか？

このメタデータは主に2つの方法で使われます:

* Web ベースの configurator が動的に UI を生成できるようにする。
* 新しい `make keyboard:keymap:qmk` ターゲットをサポートする。これは、このメタデータをファームウェアにバンドルして QMK Toolbox をよりスマートにします。

Configurator の作成者は、JSON API の使用に関する詳細について、[QMK Compiler](https://docs.api.qmk.fm/using-the-api) ドキュメントを参照することができます。
