public class Passenger {
    private final String name;
    private final Floor currentFloor;
    private final ElevatorMediator mediator;

    public Passenger(String name, Floor currentFloor, ElevatorMediator mediator) {
        this.name = name;
        this.currentFloor = currentFloor;
        this.mediator = mediator;
    }

    public String getName() {
        return name;
    }

    public int getCurrentFloor() {
        return currentFloor.getFloorNumber();
    }

    public void requestElevator(String direction) {
        System.out.println("\nPassenger " + name + " at Floor " + currentFloor.getFloorNumber() + " requests an elevator " + direction);
        mediator.requestElevator(currentFloor.getFloorNumber(), direction);
    }

    public void selectDestination(Elevator elevator, int destinationFloor) {
        System.out.println("\nPassenger " + name + " selects Floor " + destinationFloor);
        mediator.requestDestination(elevator, destinationFloor);
    }
}