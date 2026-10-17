# 🖼️ Manipulação e Tratamento de Imagens PNM — UFV

![Linguagem](https://img.shields.io/badge/Linguagem-C%2B%2B-blue.svg)
![Status](https://img.shields.io/badge/Status-Conclu%C3%ADdo-brightgreen.svg)
![UFV](https://img.shields.io/badge/INF%20110-Programa%C3%A7%C3%A3o%20I-green.svg)

Trabalho Prático desenvolvido para a disciplina **INF 110 (Programação I)** do Departamento de Informática da **Universidade Federal de Viçosa (UFV)**. O projeto realiza a leitura, manipulação e aplicação de filtros digitais em imagens no formato **PNM (P2 - Tons de Cinza e P3 - Colorido)**.

---

## 📌 Funcionalidades Principais

- **📂 Leitura e Gravação Robusta:**
  - Suporte a formatos **P2** (tons de cinza) e **P3** (colorido).
  - Estrutura unificada em matriz tridimensional `[Largura x Altura x 3 Canais (RGB)]`.
  - Tratamento de exceções na leitura com laço de repetição para arquivos inválidos.
  - Trava de segurança no salvamento para não sobrescrever a imagem original.

- **🎨 Filtros e Transformações Básicas:**
  - **Clarear e Escurecer:** Ajuste proporcional via fator $k$ ($1 \le k \le 100$) com controle de limites ($0$ a $255$).
  - **Efeito Negativo:** Inversão de cores ($255 - \text{valor}$).
  - **Espelhamento Vertical:** Inversão horizontal trocando colunas até a metade da largura.
  - **Conversão Colorida para Cinza:** Média ponderada de luminância:
    $$\text{Cinza} = 0.299 \cdot R + 0.587 \cdot G + 0.114 \cdot B$$

- **🔍 Filtros de Convolução ($3 \times 3$):**
  - **Filtro de Sobel:** Detecção e isolamento de contornos horizontais e verticais.
  - **Filtro de Realce (Sharpness):** Aumento de nitidez e destaque de detalhes.
  - Tratamento de bordas com matriz auxiliar temporária para evitar contaminação de vizinhança.

---

## ♿ Recurso Extra: Acessibilidade para Daltonismo

Módulo focado na simulação e correção visual para três tipos de daltonismo:
- **Protanopia** (ausência de receptores vermelhos)
- **Deuteranopia** (ausência de receptores verdes)
- **Tritanopia** (ausência de receptores azuis)

### ⚙️ Como Funciona:
1. **Simulação:** Multiplicação dos canais RGB por matrizes de transformação específicas para reproduzir a visão daltônica.
2. **Daltonização:** Cálculo da perda de informação de cor e reinjeção do erro nos canais visíveis, aumentando o contraste e a diferenciação entre elementos da imagem.

---

## 💻 Como Executar

1. Compile o projeto com seu compilador de preferência:
   ```bash
   g++ -o manipula_pnm main.cpp
