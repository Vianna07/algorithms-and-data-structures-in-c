// ============================================================================
// _boxes.typ — Caixas didáticas OPCIONAIS do livro (Typst).
// Injetadas no preâmbulo via _quarto-book.yml > include-in-header.
//
// As caixas PADRÃO do livro usam callouts nativos do Quarto (fonte única:
// renderizam em HTML e PDF a partir do mesmo .qmd). Estas funções existem para
// os poucos momentos em que a arte do PDF pede uma caixa sob medida.
//
// Uso, dentro de um bloco exclusivo do PDF no .qmd:
//   ::: {.content-visible when-format="pdf"}
//   ```{=typst}
//   #ideia-central[O array dobra de capacidade para amortizar o custo da cópia.]
//   ```
//   :::
// ============================================================================

// Rede de segurança: imagens (inclusive diagramas dot rasterizados) cabem na
// caixa sem cortar — "contain" preserva a proporção e nunca recorta.
#set image(fit: "contain")

#let _didatic-box(title, body, accent: rgb("#F5793B"), bg: rgb("#FBF1E8")) = block(
  width: 100%,
  inset: 12pt,
  radius: 6pt,
  fill: bg,
  stroke: (left: 3pt + accent),
  above: 10pt,
  below: 10pt,
)[
  #text(weight: "bold", fill: accent)[#title]
  #parbreak()
  #body
]

#let ideia-central(body) = _didatic-box(
  "Ideia central", body, accent: rgb("#F5793B"), bg: rgb("#FBF1E8"))

#let trade-off(body) = _didatic-box(
  "Trade-off", body, accent: rgb("#2A9D8F"), bg: rgb("#EAF4F2"))

#let big-o(body) = _didatic-box(
  "Complexidade (Big-O)", body, accent: rgb("#264653"), bg: rgb("#EEF1F6"))

#let memory-leak(body) = _didatic-box(
  "Cuidado: memory leak", body, accent: rgb("#E2725B"), bg: rgb("#FBEAE7"))

#let projetista(body) = _didatic-box(
  "Pense como projetista", body, accent: rgb("#7B5EA7"), bg: rgb("#F4EEF7"))

#let mundo-real(body) = _didatic-box(
  "No mundo real", body, accent: rgb("#F2A65A"), bg: rgb("#FFF8E6"))
