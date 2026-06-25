# Makefile — atalhos de renderização do livro-site PIESC.
#
#   make site     → _site/  (HTML interativo)
#   make book     → _book/  (PDF via Typst)
#   make all      → ambos
#   make preview  → preview do site com recarga automática
#   make clean    → remove saídas e artefatos gerados
#
# Pré-requisitos já instalados: quarto (~/.local/bin), chromium, clang-format.

# Usa o quarto do PATH; se ~/.local/bin não estiver no PATH, cai para lá.
QUARTO ?= $(shell command -v quarto 2>/dev/null || echo $(HOME)/.local/bin/quarto)

# Chrome headless usado pelo Quarto para rasterizar diagramas dot/mermaid no
# PDF (Typst). Detecta um navegador do sistema automaticamente.
export QUARTO_CHROMIUM ?= $(shell command -v chromium 2>/dev/null || command -v google-chrome-stable 2>/dev/null || command -v brave 2>/dev/null)

.PHONY: site book all preview clean

site:
	$(QUARTO) render --profile site

book:
	$(QUARTO) render --profile book

all: site book

preview:
	$(QUARTO) preview --profile site

clean:
	rm -rf _site _book .quarto _freeze index.typ
	find . -type d -name '*_files' -prune -exec rm -rf {} +
