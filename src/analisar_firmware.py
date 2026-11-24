from pathlib import Path
import hashlib

p = Path(__file__).resolve().parents[1] / "firmware" / "firmware_educacional.bin"
data = p.read_bytes()

print("Arquivo:", p.name, "| bytes:", len(data))
print("SHA-256:", hashlib.sha256(data).hexdigest())
print("Strings legiveis:")

for s in data.split(b"\x00"):
    if s:
        print(" ", s.decode("utf-8", errors="replace"))

print("AVISO: imagem didatica; nao representa firmware ESP32 real.")
