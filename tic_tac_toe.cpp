#include <iostream>
#include <vector>

enum class GameState {
    Ongoing,
    Player1Wins,
    Player2Wins,
    Draw
};

GameState check_for_win(const std::vector<std::vector<char>>& matrix) {
    for (int i = 0; i < 3; i++) {
        if (matrix[i][0] == matrix[i][1] && matrix[i][1] == matrix[i][2]) {
            return matrix[i][0] == 'X' ? GameState::Player1Wins : GameState::Player2Wins;
        }
        if (matrix[0][i] == matrix[1][i] && matrix[1][i] == matrix[2][i]) {
            return matrix[0][i] == 'X' ? GameState::Player1Wins : GameState::Player2Wins;
        }
    }

    if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2]) {
        return matrix[0][0] == 'X' ? GameState::Player1Wins : GameState::Player2Wins;
    }

    if (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0]) {
        return matrix[0][2] == 'X' ? GameState::Player1Wins : GameState::Player2Wins;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] >= '1' && matrix[i][j] <= '9') {
                return GameState::Ongoing;
            }
        }
    }

    return GameState::Draw;
}

void print_matrix(const std::vector<std::vector<char>>& matrix) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

bool change_square(int player, std::vector<std::vector<char>>& matrix, char chosen_number) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (matrix[i][j] == chosen_number) {
        matrix[i][j] = player == 1 ? 'X' : 'O';
        return true;
      }
    }
  }
  return false;
}

bool is_square_available(const std::vector<std::vector<char>>& matrix, char chosen_number) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] == chosen_number) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    bool keep_playing = true;
    while (keep_playing) {
        std::vector<std::vector<char>> matrix = {
            {'7', '8', '9'},
            {'4', '5', '6'},
            {'1', '2', '3'}
        };

        GameState game_state = GameState::Ongoing;
        int round = 0;
        while (game_state == GameState::Ongoing) {
            int player = round % 2 + 1;

            print_matrix(matrix);

            char chosen_number;
            std::cout << "Player " << player << "'s turn\n";
            bool valid_move = false;
            do {
                std::cout << "Type the number you choose: ";
                std::cin >> chosen_number;
                if (is_square_available(matrix, chosen_number)) {
                    change_square(player, matrix, chosen_number);
                    valid_move = true;
                } else {
                    std::cout << "Already chosen or not on the board, try a different square\n";
                }
                round++;
            } while (!valid_move);

            game_state = check_for_win(matrix);

            if (game_state != GameState::Ongoing) {
                print_matrix(matrix);
                if (game_state == GameState::Draw) {
                    std::cout << "It's a draw!\n";
                } else {
                    std::cout << "Player " << player << " has won!\n";
                }
            }
        }
        std::string keep_going;
        std::cout << "Type 'exit' to stop playing or type anything else to play again: ";
        std::cin >> keep_going;
        if (keep_going == "exit") {
            keep_playing = false;
        } else {
            round = 0;
        }
    }
    return 0;
}
