# 🚨 Monitor de Foco Inteligente (Smart Focus Monitor)

Este projeto é um **Detector de Distrações** em tempo real desenvolvido em Python, utilizando **OpenCV** para processamento de vídeo e **MediaPipe** (Face Mesh) para detecção de marcos faciais. O objetivo é ajudar estudantes ou profissionais a manterem o foco, monitorando sinais visuais de distração ou sonolência.

## ✨ Funcionalidades

* **Detecção Facial em Tempo Real:** Utiliza o Face Mesh do MediaPipe para mapear 478 pontos faciais.
* **Monitoramento de Indicadores de Foco:**
    * **Eye Aspect Ratio (EAR):** Detecta o fechamento dos olhos (piscadas prolongadas ou sonolência).
    * **Abertura da Boca:** Identifica bocejos ou conversas.
    * **Queda de Sobrancelha/Cabeça:** Detecta a queda da cabeça, indicando cansaço ou desinteresse.
* **Sistema de Confiança:** Utiliza um contador (`self.confidence`) para evitar falsos positivos, exigindo que o comportamento de distração persista por vários quadros antes de emitir um alerta.
* **Alerta Visual:** Exibe um status visual (`Focado ✅`, `Desfocado ❌`, `Neutro ➖`) e um **alerta vermelho piscante** na tela quando o foco é perdido.

## 🚀 Como Usar

### Pré-requisitos

Certifique-se de ter o Python instalado. Você precisará das seguintes bibliotecas:

```bash
pip install opencv-python mediapipe numpy
