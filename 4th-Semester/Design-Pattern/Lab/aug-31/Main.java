import java.util.*;

public class Main {
    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        int totalFloors = 10;
        Elevator elevator1 = new Elevator(1, 1);
        Elevator elevator2 = new Elevator(2, 5);
        Elevator elevator3 = new Elevator(3, 9);
        List<Elevator> elevators = Arrays.asList(elevator1, elevator2, elevator3);
        ElevatorController controller = new ElevatorController(totalFloors, elevators);
        Floor[] floors = new Floor[totalFloors + 1];

        for (int i = 1; i <= totalFloors; i++) {
            floors[i] = new Floor(i);
            floors[i].setMediator(controller);
        }

        System.out.println("==========================================");
        System.out.println("       ELEVATOR CONTROL SYSTEM");
        System.out.println("       Mediator Design Pattern");
        System.out.println("==========================================");
        runMenu(controller, floors, elevators);
        scanner.close();
    }

    private static void runMenu(
        ElevatorController controller, Floor[] floors, List<Elevator> elevators) {
        while (true) {
            System.out.println("\n============== MENU ==============");
            System.out.println("1. Request Elevator");
            System.out.println("2. Select Destination");
            System.out.println("3. Show Elevator Status");
            System.out.println("4. Exit");
            System.out.println("==================================");
            System.out.print("Enter choice: ");
            int choice = readInt();

            switch (choice) {
                case 1:
                    requestElevator(floors);
                    break;

                case 2:
                    selectDestination(controller, elevators);
                    break;

                case 3:
                    controller.showElevatorStatus();
                    break;

                case 4:
                    System.out.println("Exiting system...");
                    return;

                default:
                    System.out.println("Invalid choice.");
            }
        }
    }

    private static void requestElevator(Floor[] floors) {
        System.out.print("Enter current floor: ");

        int floorNumber = readInt();

        if (floorNumber < 1 || floorNumber >= floors.length) {
            System.out.println("Invalid floor.");
            return;
        }

        System.out.print("Enter direction (UP/DOWN): ");
        String direction = scanner.nextLine().trim().toUpperCase();

        if (direction.equals("UP")) {
            floors[floorNumber].pressUpButton();
        } else if (direction.equals("DOWN")) {
            floors[floorNumber].pressDownButton();
        } else {
            System.out.println("Invalid direction.");
        }
    }

    private static void selectDestination(ElevatorController controller, List<Elevator> elevators) {
        System.out.print("Enter elevator ID: ");
        int elevatorId = readInt();
        Elevator selectedElevator = null;

        for (Elevator elevator : elevators) {
            if (elevator.getId() == elevatorId) {
                selectedElevator = elevator;
                break;
            }
        }

        if (selectedElevator == null) {
            System.out.println("Elevator not found.");
            return;
        }

        if (selectedElevator.getStatus() != Elevator.Status.DOOR_OPEN) {
            System.out.println("Elevator " + elevatorId + " does not have its doors open.");
            return;
        }

        System.out.print("Enter destination floor: ");
        int destination = readInt();
        controller.requestDestination(selectedElevator, destination);
    }

    private static int readInt() {
        while (true) {
            try {
                return Integer.parseInt(scanner.nextLine().trim());

            } catch (NumberFormatException e) {
                System.out.print("Please enter a valid number: ");
            }
        }
    }
}