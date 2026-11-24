# Analise das comunicacoes

O laboratorio Python demonstra um payload JSON
legivel localmente.

Nao realiza captura real de Wi-Fi, MQTT ou HTTP.

A demonstracao utiliza HMAC-SHA256 para verificar
integridade de mensagens.

HMAC nao fornece confidencialidade.

Em um equipamento real, verificar:
- Protocolo e portas
- Origem e destino
- Autenticacao
- TLS e certificados
- Dados transmitidos
- Mensagens de controle
