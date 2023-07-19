class Player
{
private:
    std::string player_name;
    int player_score;
public:
    Player(/* args */);
    ~Player();
    void setPlayerName(std::string player_name);
    void setPlayerScore(int player_score);
    std::string getPlayerName();
    int getPlayerScore();
};
