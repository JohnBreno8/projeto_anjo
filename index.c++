#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

// Configuração básica
const int MAX_DEVICES = 1000; // Número máximo de dispositivos
const int PORT = 8080;        // Porta para conexão

// Função para inicializar SSL
SSL_CTX* InitSSL() {
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    SSL_CTX* ctx = SSL_CTX_new(TLS_server_method());
    if (!ctx) {
        std::cerr << "Erro ao inicializar SSL!" << std::endl;
        exit(EXIT_FAILURE);
    }
    return ctx;
}

// Classe para gerenciar conexões
class NetworkNode {
public:
    void startServer() {
        int server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == 0) {
            perror("Socket falhou");
            exit(EXIT_FAILURE);
        }

        struct sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);

        if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
            perror("Bind falhou");
            exit(EXIT_FAILURE);
        }

        if (listen(server_fd, MAX_DEVICES) < 0) {
            perror("Listen falhou");
            exit(EXIT_FAILURE);
        }

        std::cout << "Servidor iniciado na porta " << PORT << std::endl;

        while (true) {
            int new_socket = accept(server_fd, NULL, NULL);
            if (new_socket < 0) {
                perror("Erro ao aceitar conexão");
                continue;
            }
            std::thread(&NetworkNode::handleClient, this, new_socket).detach();
        }
    }

private:
    SSL_CTX* ssl_ctx;

    void handleClient(int client_socket) {
        SSL* ssl = SSL_new(ssl_ctx);
        SSL_set_fd(ssl, client_socket);

        if (SSL_accept(ssl) <= 0) {
            ERR_print_errors_fp(stderr);
        } else {
            char buffer[1024] = {0};
            SSL_read(ssl, buffer, sizeof(buffer));
            std::cout << "Mensagem recebida: " << buffer << std::endl;

            std::string response = "Mensagem recebida com sucesso!";
            SSL_write(ssl, response.c_str(), response.size());
        }
        SSL_free(ssl);
        close(client_socket);
    }

public:
    NetworkNode() {
        ssl_ctx = InitSSL();
    }

    ~NetworkNode() {
        SSL_CTX_free(ssl_ctx);
    }
};

int main() {
    NetworkNode networkNode;
    networkNode.startServer();
    return 0;
}
