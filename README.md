Como o Sistema de Segurança Funciona

Este sistema conecta um programa C++ (que controla o menu do "Projeto ANJO") a um script Python (que age como cliente de segurança). Vamos explicar tudo em detalhes, desde como cada parte funciona até como elas interagem.


---

Divisão do Sistema

1. Servidor em C++ (Menu do Projeto ANJO):

Controla o menu interativo.

Funciona como um servidor socket aguardando conexões.

Recebe mensagens de segurança enviadas pelo script Python e as exibe no menu.



2. Cliente em Python (Sistema de Segurança):

Verifica a autenticação do usuário.

Envia mensagens (como logs ou alertas) para o servidor em C++.

Simula um monitoramento constante, permitindo o envio de informações dinâmicas.



3. Comunicação via Socket:

A comunicação entre o servidor e o cliente acontece via protocolo TCP, utilizando sockets.

O servidor C++ aguarda conexões na porta 8080.

O cliente Python se conecta à porta 8080 e troca mensagens com o servidor.





---

Explicação do Código do Servidor (C++)

O programa em C++ tem duas responsabilidades principais:

1. Exibir o Menu do "Projeto ANJO".


2. Aguardar mensagens do sistema de segurança em Python.



Principais Componentes do Código

1. Configuração do Servidor Socket

Criamos um socket para aceitar conexões de um cliente:

int server_fd, new_socket;
server_fd = socket(AF_INET, SOCK_STREAM, 0);
bind(server_fd, (struct sockaddr*)&address, sizeof(address));
listen(server_fd, 3);
new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);

O servidor aguarda conexões na porta 8080.



2. Exibição do Menu

Usamos a biblioteca ncurses para criar um menu interativo.

A função displayLogo imprime a logo "Projeto ANJO".

A função principal exibe as opções do menu e permite navegação com as setas.



3. Recebimento de Mensagens

Quando o cliente Python envia uma mensagem, ela é recebida com:

read(new_socket, buffer, 1024);
mvwprintw(menuWin, 18, 4, "Mensagem do Python: %s", buffer);

As mensagens são exibidas diretamente no menu.



4. Encerramento

Após finalizar a interação, os sockets são fechados:

close(new_socket);
close(server_fd);





---

Explicação do Código do Cliente (Python)

O script Python age como um cliente que envia mensagens ao servidor. Ele também tem autenticação para garantir segurança.

Principais Componentes do Código

1. Autenticação

O script solicita ao usuário uma senha antes de se conectar ao servidor:

senha = input("Digite a senha de autenticação: ")
if senha == "anjo2024":
    print("Acesso autorizado!")

Apenas usuários autenticados conseguem interagir com o servidor.



2. Conexão com o Servidor

Após a autenticação, o script conecta-se ao servidor C++:

s.connect((HOST, PORT))
print("Conectado ao servidor do Projeto ANJO.")



3. Envio de Mensagens

O script permite que o usuário envie mensagens que são exibidas no menu do servidor:

mensagem = input("Mensagem de segurança: ")
s.sendall(mensagem.encode())



4. Monitoramento Contínuo

O script simula monitoramento com um loop, permitindo envio de mensagens em tempo real.





---

Funcionamento Geral

Fluxo de Execução

1. Início do Servidor

O programa em C++ é iniciado. Ele configura o servidor e aguarda conexões na porta 8080.



2. Autenticação do Cliente

O script Python solicita uma senha para autenticar o usuário.



3. Conexão

Após a autenticação, o script Python conecta-se ao servidor.



4. Troca de Mensagens

O cliente Python envia mensagens (logs, alertas, ou comandos) para o servidor C++.

As mensagens aparecem no menu interativo do "Projeto ANJO".





---

Exemplo Prático

Servidor (C++)

1. Compile e execute o servidor:

g++ -o projeto_anjo menu_socket.cpp -lncurses
./projeto_anjo


2. O servidor exibe o menu interativo e aguarda mensagens.



Cliente (Python)

1. Execute o cliente:

python3 sistema_seguranca.py


2. Digite a senha (anjo2024) para autenticar.


3. Envie mensagens que aparecerão no servidor.




---

Vantagens do Sistema

1. Segurança:

O script Python exige autenticação antes de enviar mensagens ao servidor.

Apenas clientes autorizados podem interagir com o menu.



2. Flexibilidade:

Permite adicionar funcionalidades extras no cliente Python, como envio de logs ou comandos.



3. Interatividade:

As mensagens enviadas pelo Python são exibidas diretamente no menu do C++.





---

Como Expandir

1. Adicionar Criptografia

Use bibliotecas como SSL/TLS para criptografar as mensagens trocadas entre cliente e servidor.



2. Autenticação Avançada

Implemente autenticação baseada em tokens ou chaves públicas/privadas.



3. Logs no Servidor

Armazene mensagens recebidas pelo servidor em um arquivo de log.



4. Comandos Dinâmicos

Permita que o cliente Python envie comandos para controlar o menu do servidor (por exemplo, iniciar um serviço ou alterar configurações).
