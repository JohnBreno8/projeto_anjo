import socket
import time

# Configuração do cliente socket
HOST = "127.0.0.1"  # IP do servidor (localhost)
PORT = 8080         # Porta do servidor

def autenticar():
    print("Sistema de Segurança - Projeto ANJO")
    senha = input("Digite a senha de autenticação: ")
    if senha == "anjo2024":
        print("Acesso autorizado!")
        return True
    else:
        print("Acesso negado!")
        return False

if autenticar():
    # Conectar ao servidor em C++
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        print("Conectado ao servidor do Projeto ANJO.")
        
        while True:
            # Enviar mensagem para o servidor
            mensagem = input("Mensagem de segurança: ")
            s.sendall(mensagem.encode())
            
            # Simular monitoramento
            time.sleep(2)
