class Player
{
private:
    std::string player_name;
    int player_score;
    double player_time;
public:
    Player(/* args */);
    ~Player();
    void setPlayerName(std::string player_name);
    void setPlayerScore(int player_score);
    void setPlayerTime(double player_time);
    std::string getPlayerName();
    int getPlayerScore();
    double getPlayerTime();
};
