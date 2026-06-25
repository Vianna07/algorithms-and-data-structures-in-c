/**
 * typing-effect.js — Typewriter reveal for chapter/section titles (HTML only).
 *
 * Targets any element carrying the `.typing-effect` class, produced from the
 * Pandoc span/header syntax in the .qmd sources, e.g.:
 *
 *     # [Título Animado]{.typing-effect}
 *
 * Behaviour & graceful degradation:
 *   - The animation starts only when the title scrolls into view
 *     (IntersectionObserver), so it reads as intentional, not janky.
 *   - Honours `prefers-reduced-motion`: the final text is shown instantly.
 *   - If JS is disabled the original text is already in the DOM.
 *
 * Wired site-wide via `_quarto-site.yml > include-after-body`. It is never
 * loaded by the PDF (Typst) build, which uses a plain static title instead.
 */
(function () {
  "use strict";

  var SELECTOR = ".typing-effect";
  var CHAR_DELAY_MS = 45; // tempo entre caracteres
  var START_DELAY_MS = 200; // pausa antes de começar a digitar

  var reduceMotion =
    window.matchMedia &&
    window.matchMedia("(prefers-reduced-motion: reduce)").matches;

  function typeInto(el) {
    if (el.dataset.typed === "true") return; // nunca repete no mesmo elemento
    el.dataset.typed = "true";

    var fullText = el.textContent;
    if (reduceMotion || !fullText) return; // mantém o texto final, sem animar

    el.textContent = "";
    el.classList.add("typing-effect--running"); // ativa o cursor piscante (CSS)

    var i = 0;
    function step() {
      el.textContent = fullText.slice(0, i);
      if (i <= fullText.length) {
        i += 1;
        window.setTimeout(step, CHAR_DELAY_MS);
      } else {
        el.classList.remove("typing-effect--running");
        el.classList.add("typing-effect--done");
      }
    }
    window.setTimeout(step, START_DELAY_MS);
  }

  function init() {
    var nodes = Array.prototype.slice.call(
      document.querySelectorAll(SELECTOR)
    );
    if (!nodes.length) return;

    // Fallback para navegadores sem IntersectionObserver: digita tudo logo.
    if (!("IntersectionObserver" in window)) {
      nodes.forEach(typeInto);
      return;
    }

    var io = new IntersectionObserver(
      function (entries) {
        entries.forEach(function (entry) {
          if (entry.isIntersecting) {
            typeInto(entry.target);
            io.unobserve(entry.target);
          }
        });
      },
      { threshold: 0.6 }
    );

    nodes.forEach(function (n) {
      io.observe(n);
    });
  }

  if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", init);
  } else {
    init();
  }
})();
