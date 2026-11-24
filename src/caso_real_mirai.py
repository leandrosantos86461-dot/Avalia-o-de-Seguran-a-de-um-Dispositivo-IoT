"""Demonstração local inspirada no Mirai (2016). Sem rede ou alvos externos."""
import hashlib
import hmac
import json
import secrets

DISPOSITIVO = "NexaSense-LAB-01"
SENHA_PADRAO = "admin"  # APENAS EXEMPLO FICTÍCIO DO LABORATÓRIO


def senha_segura(senha, sal=None):
    sal = sal or secrets.token_bytes(16)
    derivada = hashlib.pbkdf2_hmac("sha256", senha.encode(), sal, 200_000)
    return sal, derivada


def verificar_senha(senha, sal, derivada):
    candidata = hashlib.pbkdf2_hmac("sha256", senha.encode(), sal, 200_000)
    return hmac.compare_digest(candidata, derivada)


def demonstrar():
    print("=== CASO REAL: MIRAI (2016) — SIMULACAO EDUCATIVA ===")
    print("O Mirai explorou dispositivos IoT com credenciais fracas ou padrao.")
    print("Nao estamos executando o Mirai nem acessando dispositivos reais.\n")
    print("[1] ANTES: credencial padrao no dispositivo ficticio")
    print("Dispositivo:", DISPOSITIVO)
    print("Login com senha padrao aceito:", SENHA_PADRAO == "admin")
    print("Risco: credenciais conhecidas facilitam acesso nao autorizado.\n")
    print("[2] DEPOIS: senha individual e verificacao protegida")
    senha_individual = secrets.token_urlsafe(18)
    sal, derivada = senha_segura(senha_individual)
    print("Senha padrao aceita:", verificar_senha("admin", sal, derivada))
    print("Senha individual aceita:", verificar_senha(senha_individual, sal, derivada))
    print("Senha armazenada em claro: False (somente derivacao + sal)")
    print("Recomendacao: credenciais unicas, limite de tentativas e atualizacoes.\n")
    print("[3] COMUNICACAO: exemplo de telemetria legivel")
    mensagem = json.dumps({"dispositivo": DISPOSITIVO, "temperatura": 24.5})
    print("Mensagem sem criptografia:", mensagem)
    print("Recomendacao: usar TLS para proteger dados em transito.")
    print("=== FIM DA DEMONSTRACAO LOCAL ===")


if __name__ == "__main__":
    demonstrar()
