class Player
{
private:
    std::string player_name;
    int player_score;
    double player_time;
    int player_correct_answer_count;
public:
    Player(/* args */);
    ~Player();
    void setPlayerName(std::string player_name);
    void setPlayerScore(int player_score);
    void setPlayerTime(double player_time);
    void setPlayerCorrectAnswerCount(int player_correct_answer_count);
    std::string getPlayerName();
    int getPlayerScore();
    double getPlayerTime();
    void calculatePlayerScore();
    void printPlayerScore();
    void savePlayerScore();
};
