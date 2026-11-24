# Achados e classificacao

| ID | Evidencia observada | Impacto | Probabilidade | Risco | Recomendacao | Status |
|---|---|---|---|---|---|---|
| F01 | `evidence/laboratorio_saida.txt`: JSON aparece legivel no terminal | Medio, se transmitido em canal aberto | Condicional, nao medida | Medio ilustrativo | TLS com validacao de certificados e autenticacao | Demonstrado apenas localmente |
| F02 | `evidence/analisar_firmware_saida.txt`: `debug_enabled=true` em imagem artificial | Medio se logs revelarem dados | Condicional, nao medida | Medio ilustrativo | Desabilitar logs sensiveis na versao comercial | Confirmado apenas na imagem didatica |
| H01 | Nenhuma inspecao de UART/JTAG realizada | Potencialmente alto | Nao avaliada | Nao classificado | Inspecionar placa e restringir debug | Hipotese |
| H02 | Nenhum mecanismo de atualizacao real avaliado | Potencialmente alto | Nao avaliada | Nao classificado | Assinatura, validacao e anti-rollback | Hipotese |

**Importante:** JSON legivel em uma simulacao nao comprova trafego de rede desprotegido. Uma flag de debug em arquivo artificial nao comprova vulnerabilidade de produto comercial.

## Cadeia evidencia → fragilidade → ameaca → impacto → mitigacao
F01: JSON legivel no console → confidencialidade nao demonstrada → observador em hipotetico canal aberto → leitura indevida → TLS/autenticacao.
F02: flag debug ativa na imagem didatica → possivel logging excessivo → atacante com acesso ao console em hipotetico produto → divulgacao de informacao → reduzir debug em producao.

## Referencias associadas
OWASP ISTG: metodologia de identificacao de superficies e testes; NIST IR 8259A: protecao de dados e controle de interfaces; ETSI EN 303 645: comunicacao segura e credenciais; MITRE EMB3D: ameacas embarcadas; Espressif ESP-IDF: Secure Boot, Flash Encryption e depuracao.
