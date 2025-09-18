public class Account {

    private String username;
    private String password;
    private String vote;

    public Account(String username, String password) {
        this.username = username;
        this.password = password;
    }

    public void setVote(String vote) {
        this.vote = vote;
    }

    public String getVote() {
        return vote;
    }

    public String getUsername() {
        return username;
    }
    public String getPassword() {
        return password;
    }
}
