public class ElevatorRequest {
    private final int requestingFloor;
    private final String direction;
    private Integer destinationFloor;

    public ElevatorRequest(int requestingFloor, String direction) {
        this.requestingFloor = requestingFloor;
        this.direction = direction;
    }

    public int getRequestingFloor() {
        return requestingFloor;
    }

    public String getDirection() {
        return direction;
    }

    public Integer getDestinationFloor() {
        return destinationFloor;
    }

    public void setDestinationFloor(int destinationFloor) {
        this.destinationFloor = destinationFloor;
    }

    @Override
    public String toString() {
        return "Floor: " + requestingFloor + ", Direction: " + direction + (destinationFloor != null ? ", Destination: " + destinationFloor : "");
    }
}