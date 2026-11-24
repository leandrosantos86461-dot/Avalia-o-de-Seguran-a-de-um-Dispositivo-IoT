"""Simulacao local de telemetria. Nenhuma conexao externa."""
import json
import hashlib
import hmac
import secrets

mensagem = {
    "dispositivo": "NexaSense-LAB-01",
    "temperatura": 24.5,
    "umidade": 56
}

texto = json.dumps(mensagem, ensure_ascii=False, sort_keys=True)

print("=== CENARIO 1: exposicao de telemetria em texto claro ===")
print("Payload visivel:", texto)
print("Risco: dados podem ser lidos em um canal sem protecao.")

print("=== CENARIO 2: verificacao de integridade ===")
chave = secrets.token_bytes(32)
assinatura = hmac.new(chave, texto.encode(), hashlib.sha256).hexdigest()

print("Assinatura HMAC:", assinatura)
print("Integridade valida:", hmac.compare_digest(
    assinatura,
    hmac.new(chave, texto.encode(), hashlib.sha256).hexdigest()
))
print("Mensagem alterada valida:", hmac.compare_digest(
    assinatura,
    hmac.new(chave, (texto + "!").encode(), hashlib.sha256).hexdigest()
))
print("NOTA: HMAC nao criptografa. Em producao, usar TLS.")
