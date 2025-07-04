public class Account{
    String id;
    String name;
    int balance;

    Account(String id, String name) {
        this.id = id;
        this.name = name;
        this.balance = 0;
    }
    Account(String id, String name, int balance) {
        this.id = id;
        this.name = name;
        this.balance = balance;
    }
    public String getId() {
        return id;
    }
    public String getName() {
        return name;
    }
    public int getBalance() {
        return balance;
    }
    public int credit(int balance) {
        this.balance = this.balance + balance;
        return this.balance;
    }
    public int debit(int balance) {
        if (balance < this.balance) {
            this.balance = this.balance - balance;
        } else {
            System.out.println("Amount exceeded balance");
        }
        return this.balance;
    }
    public int transferTo(Account account, int balance) {
        debit(balance);
        account.credit(balance);
        return this.balance;
    }
    public String toString() {
        return "Account[id=" + this.id + ",name=" + this.name + ",balance=" + this.balance;
    }
}