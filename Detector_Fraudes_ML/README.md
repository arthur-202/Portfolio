# Detecção de Fraudes com Regressão Logística

## Sobre o Projeto

Este projeto tem como objetivo desenvolver um modelo de **Detecção de Fraudes em Transações Financeiras** utilizando **Regressão Logística**.

O foco principal é a aplicação prática de conceitos de **Machine Learning supervisionado**, incluindo:

- Pré-processamento de dados
- Engenharia de features
- Treinamento e validação de modelo
- Avaliação com métricas apropriadas para classificação
- Visualização de desempenho

O projeto possui caráter **educacional e experimental**, buscando consolidar fundamentos de modelagem preditiva aplicados ao problema de fraude.

---

## Objetivos

- Aplicar Regressão Logística em um problema real
- Trabalhar com bases de dados desbalanceadas
- Avaliar desempenho do modelo com métricas robustas
- Demonstrar capacidade de separação entre classes fraudulentas e legítimas
- Produzir documentação clara e reprodutível

---

## Base de Dados

A base utilizada foi obtida do **Kaggle** e também está disponível neste repositório para fins educacionais.

Ela contém registros de transações financeiras rotuladas como:

- 0 → Transação legítima 
- 1 → Transação fraudulenta 

---

## Tecnologias Utilizadas

- Python
- Pandas
- NumPy
- Scikit-learn
- Matplotlib
- Seaborn
- Google Colab / Jupyter Notebook

---

## Metodologia

### Pré-processamento
- Tratamento de variáveis categóricas
- Normalização de variáveis numéricas
- Separação entre treino e teste
- Pipeline de transformação de dados

---

### Modelagem

Foi utilizado o algoritmo:

> **Regressão Logística**

Este modelo foi escolhido por:

- Alta interpretabilidade
- Forte baseline para problemas de classificação
- Ampla utilização em cenários reais de risco e fraude

---

### Avaliação do Modelo

O desempenho foi avaliado utilizando:

- Matriz de confusão
- Curva ROC
- AUC (Área sob a Curva)
- Comparação entre valores reais e probabilidades previstas

O modelo apresentou:

> **AUC ≈ 0.89**

Indicando boa capacidade de separação entre classes.

---

## Resultados

A análise gráfica demonstrou que o modelo consegue identificar padrões relevantes associados a fraudes, mantendo desempenho significativamente superior ao acaso.

O uso da Curva ROC evidenciou o trade-off entre:

- Taxa de detecção de fraudes
- Falsos positivos

---


## Como Executar o Projeto

### Clonar o repositório
```bash
git clone https://github.com/arthur-202/Portfolio/tree/main/Detector_Fraudes_ML

