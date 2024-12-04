#include <iostream>
#include <ncurses.h>
#include <vector>
#include <string>

// Logo estilizada
void displayLogo(WINDOW* win) {
    int start_x = 2; // Posição horizontal da logo
    int start_y = 1; // Posição vertical da logo

    mvwprintw(win, start_y, start_x, " ██████╗ ██████╗  ██████╗ ███████╗████████╗ ██████╗ ");
    mvwprintw(win, start_y + 1, start_x, "██╔════╝██╔═══██╗██╔═══██╗██╔════╝╚══██╔══╝██╔═══██╗");
    mvwprintw(win, start_y + 2, start_x, "██║     ██║   ██║██║   ██║███████╗   ██║   ██║   ██║");
    mvwprintw(win, start_y + 3, start_x, "██║     ██║   ██║██║   ██║╚════██║   ██║   ██║   ██║");
    mvwprintw(win, start_y + 4, start_x, "╚██████╗╚██████╔╝╚██████╔╝███████║   ██║   ╚██████╔╝");
    mvwprintw(win, start_y + 5, start_x, " ╚═════╝ ╚═════╝  ╚═════╝ ╚══════╝   ╚═╝    ╚═════╝ ");
    mvwprintw(win, start_y + 6, start_x, "                   Projeto ANJO                   ");
    wrefresh(win);
}

// Função para exibir o menu
int displayMenu(WINDOW* win, std::vector<std::string> options, int highlight) {
    int start_y = 10; // Começo do menu
    int start_x = 4;  // Espaço lateral

    for (int i = 0; i < options.size(); i++) {
        if (i == highlight) {
            wattron(win, A_REVERSE); // Destaque para a opção selecionada
            mvwprintw(win, start_y + i, start_x, options[i].c_str());
            wattroff(win, A_REVERSE);
        } else {
            mvwprintw(win, start_y + i, start_x, options[i].c_str());
        }
    }
    wrefresh(win);
    return highlight;
}

// Função principal
int main() {
    initscr(); // Inicia o modo ncurses
    noecho();  // Não exibe os caracteres digitados
    cbreak();  // Permite que as teclas sejam lidas instantaneamente
    keypad(stdscr, TRUE); // Habilita as teclas de função
    curs_set(0); // Oculta o cursor

    int highlight = 0;
    int choice = -1;
    int input;

    std::vector<std::string> menuOptions = {
        "1. Iniciar Servidor",
        "2. Configurações",
        "3. Ajuda",
        "4. Sair"
    };

    // Configuração da janela principal
    int height = 20, width = 60;
    int start_y = (LINES - height) / 2;
    int start_x = (COLS - width) / 2;
    WINDOW* menuWin = newwin(height, width, start_y, start_x);
    box(menuWin, 0, 0);

    displayLogo(menuWin); // Exibe a logo
    while (choice == -1) {
        highlight = displayMenu(menuWin, menuOptions, highlight);

        // Controle de entrada
        input = wgetch(menuWin);
        switch (input) {
            case KEY_UP:
                if (highlight > 0)
                    highlight--;
                break;
            case KEY_DOWN:
                if (highlight < menuOptions.size() - 1)
                    highlight++;
                break;
            case 10: // Enter
                choice = highlight;
                break;
            default:
                break;
        }
    }

    // Limpa a tela e exibe a opção escolhida
    clear();
    mvprintw(0, 0, "Você escolheu a opção: %s", menuOptions[choice].c_str());
    refresh();
    getch();

    // Finaliza ncurses
    endwin();
    return 0;
}
