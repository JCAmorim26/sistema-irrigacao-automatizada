# Automate: Sistema de Irrigação Automatizado 🍅💧

Este projeto documenta o desenvolvimento de um sistema de automação voltado para a agricultura de precisão (irrigação de uma plantação de tomates), utilizando controle de tempo real para otimização do uso hídrico.

## 🛠️ Tecnologias e Componentes
* **Microcontrolador:** Plataforma base compatível com C/C++.
* **Módulo de Tempo Real (RTC):** Módulo DS3231 (alta precisão para registro de horário e calendário).
* **Atuadores:** Sistema de bombeamento/válvulas para liberação controlada de água.

## ⚙️ Funcionalidades Implementadas
* **Acionamento Agendado:** O sistema realiza a leitura contínua do horário exato através do módulo RTC, eliminando a dependência da função `delay()` ou contadores internos imprecisos do microcontrolador.
* **Automação Baseada em Condições:** A lógica de programação aciona os atuadores de irrigação estritamente dentro das janelas de tempo pré-configuradas no código, garantindo a rega no momento térmico ideal para a plantação.
* **Base para Automação Predial:** A arquitetura lógica desenvolvida neste projeto (acionamento de cargas via relógio de tempo real) é diretamente escalável para rotinas de automação predial, como controle de iluminação e climatização (HVAC).

## 📌 Status do Projeto
O código-fonte e a lógica de acionamento via RTC foram totalmente implementados e testados, validando o conceito de automação temporal para sistemas físicos.
