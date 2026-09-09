public class Elevator {
    public enum Status { IDLE, MOVING_UP, MOVING_DOWN, DOOR_OPEN }

    private final int id;
    private int currentFloor;
    private Status status;

    private ElevatorMediator mediator;

    public Elevator(int id, int initialFloor) {
        this.id = id;
        this.currentFloor = initialFloor;
        this.status = Status.IDLE;
    }

    public void setMediator(ElevatorMediator mediator) {
        this.mediator = mediator;
    }

    public int getId() {
        return id;
    }

    public int getCurrentFloor() {
        return currentFloor;
    }

    public Status getStatus() {
        return status;
    }

    public boolean isIdle() {
        return status == Status.IDLE;
    }

    public void moveTo(int targetFloor) {
        if (targetFloor == currentFloor) {
            System.out.println("Elevator " + id + " is already at Floor " + currentFloor);
            openDoor();
            return;
        }

        if (targetFloor > currentFloor) {
            status = Status.MOVING_UP;
        } else {
            status = Status.MOVING_DOWN;
        }

        System.out.println("Elevator " + id + " moving from Floor " + currentFloor + " to Floor " + targetFloor);

        while (currentFloor != targetFloor) {
            if (currentFloor < targetFloor) {
                currentFloor++;
            } else {
                currentFloor--;
            }

            System.out.println("Elevator " + id + " -> Floor " + currentFloor);
        }

        openDoor();
    }

    public void openDoor() {
        status = Status.DOOR_OPEN;

        System.out.println("Elevator " + id + " doors OPEN at Floor " + currentFloor);
    }

    public void closeDoor() {
        System.out.println("Elevator " + id + " doors CLOSED");

        status = Status.IDLE;

        if (mediator != null) {
            mediator.elevatorBecameAvailable(this);
        }
    }

    public void displayStatus() {
        System.out.printf("Elevator %d | Floor: %d | Status: %s%n", id, currentFloor, status);
    }
}