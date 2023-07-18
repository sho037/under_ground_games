class Game
{
private:
    std::string game_name;
    std::string game_mode;
public:
    Game();
    ~Game();
    void setGameMode(std::string game_mode);
};