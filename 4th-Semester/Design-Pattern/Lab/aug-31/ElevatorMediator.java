public interface ElevatorMediator {
    void requestElevator(int floorNumber, String direction);
    void requestDestination(Elevator elevator, int destinationFloor);
    void elevatorBecameAvailable(Elevator elevator);
    void showElevatorStatus();
}