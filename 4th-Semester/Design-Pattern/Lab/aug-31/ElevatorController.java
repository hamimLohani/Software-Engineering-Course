import java.util.*;

public class ElevatorController implements ElevatorMediator {
    private final List<Elevator> elevators;
    private final Queue<ElevatorRequest> pendingRequests;
    private final int totalFloors;

    public ElevatorController(int totalFloors, List<Elevator> elevators) {
        this.totalFloors = totalFloors;
        this.elevators = elevators;
        this.pendingRequests = new LinkedList<>();
        for (Elevator elevator : elevators) {
            elevator.setMediator(this);
        }
    }

    @Override
    public void requestElevator(int floorNumber, String direction) {
        if (floorNumber < 1 || floorNumber > totalFloors) {
            System.out.println("Invalid floor number.");
            return;
        }
        if (!direction.equalsIgnoreCase("UP") && !direction.equalsIgnoreCase("DOWN")) {
            System.out.println("Invalid direction.");
            return;
        }
        ElevatorRequest request = new ElevatorRequest(floorNumber, direction.toUpperCase());
        Elevator elevator = findNearestIdleElevator(floorNumber);
        
        if (elevator == null) {
            System.out.println("All elevators are busy.");
            System.out.println("Request added to waiting queue.");
            pendingRequests.add(request);
            return;
        }
        System.out.println("Controller selected Elevator " + elevator.getId());
        elevator.moveTo(floorNumber);
        System.out.println("Passenger can now enter Elevator " + elevator.getId());
    }

    @Override
    public void requestDestination(Elevator elevator, int destinationFloor) {
        if (destinationFloor < 1 || destinationFloor > totalFloors) {
            System.out.println("Invalid destination floor.");
            return;
        }
        ElevatorRequest request = new ElevatorRequest(elevator.getCurrentFloor(), "DESTINATION");
        request.setDestinationFloor(destinationFloor);
        System.out.println("Controller received destination request: " + request);
        elevator.closeDoor();
        elevator.moveTo(destinationFloor);
    }

    @Override
    public void elevatorBecameAvailable(Elevator elevator) {
        System.out.println("\nController: Elevator " + elevator.getId() + " is now available.");
        processPendingRequests();
    }

    private Elevator findNearestIdleElevator(int requestedFloor) {
        Elevator nearest = null;
        int minimumDistance = Integer.MAX_VALUE;
        for (Elevator elevator : elevators) {
            if (!elevator.isIdle()) {
                continue;
            }
            int distance = Math.abs(elevator.getCurrentFloor() - requestedFloor);
            if (distance < minimumDistance) {
                minimumDistance = distance;
                nearest = elevator;
            }
        }
        return nearest;
    }

    private void processPendingRequests() {
        if (pendingRequests.isEmpty()) {
            return;
        }
        Iterator<ElevatorRequest> iterator = pendingRequests.iterator();
        while (iterator.hasNext()) {
            ElevatorRequest request = iterator.next();
            Elevator elevator = findNearestIdleElevator(request.getRequestingFloor());
            if (elevator == null) {
                return;
            }
            System.out.println("\nProcessing waiting request: " + request);
            iterator.remove();
            elevator.moveTo(request.getRequestingFloor());
            System.out.println("Elevator " + elevator.getId() + " arrived for waiting passenger.");
        }
    }

    @Override
    public void showElevatorStatus() {
        System.out.println("\n========== ELEVATOR STATUS ==========");

        for (Elevator elevator : elevators) {
            elevator.displayStatus();
        }

        System.out.println("Waiting Requests: " + pendingRequests.size());

        System.out.println("======================================");
    }
}