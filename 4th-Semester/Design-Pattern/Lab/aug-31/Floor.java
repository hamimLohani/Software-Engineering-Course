public class Floor {
    private final int floorNumber;
    private ElevatorMediator mediator;

    public Floor(int floorNumber) {
        this.floorNumber = floorNumber;
    }

    public void setMediator(ElevatorMediator mediator) {
        this.mediator = mediator;
    }

    public int getFloorNumber() {
        return floorNumber;
    }

    public void pressUpButton() {
        System.out.println("\nPassenger at Floor " + floorNumber + " pressed UP");
        mediator.requestElevator(floorNumber, "UP");
    }

    public void pressDownButton() {
        System.out.println("\nPassenger at Floor " + floorNumber + " pressed DOWN");
        mediator.requestElevator(floorNumber, "DOWN");
    }
}