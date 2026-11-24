import subprocess
import sys
from pathlib import Path

base = Path(__file__).resolve().parent

casos = [
    ("analisar_firmware.py", ["SHA-256", "debug_enabled=true"]),
    ("caso_real_mirai.py", ["Senha padrao aceita: False", "Senha individual aceita: True"]),
    ("laboratorio.py", [
        "Integridade valida: True",
        "Mensagem alterada valida: False"
    ])
]

for nome, termos in casos:
    p = subprocess.run(
        [sys.executable, str(base / nome)],
        capture_output=True,
        text=True,
        check=True
    )
    assert all(t in p.stdout for t in termos), p.stdout
    print("OK:", nome)

print("TODOS OS TESTES PASSARAM")
