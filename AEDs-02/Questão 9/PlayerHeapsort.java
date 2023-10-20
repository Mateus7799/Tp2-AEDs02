import java.io.*;
import java.util.*;

class Player {
    int id;
    String name;
    int height;
    int weight;
    String born;
    String college;
    String birthCity;
    String birthState;

    public Player(int id, String name, int height, int weight, String born, String college, String birthCity, String birthState) {
        this.id = id;
        this.name = name;
        this.height = height;
        this.weight = weight;
        this.born = born;
        this.college = college;
        this.birthCity = birthCity;
        this.birthState = birthState;
    }

    public String toString() {
        return "[" + id + " ## " + name + " ## " + height + " ## " + weight + " ## " + born + " ## " + college + " ## " + birthCity + " ## " + birthState + "]";
    }
}

public class PlayerHeasport {

    public static void heapSort(Player[] arr) {
        int n = arr.length;

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        for (int i = n - 1; i > 0; i--) {
            Player temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            heapify(arr, i, 0);
        }
    }

    public static void heapify(Player[] arr, int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && arr[l].height > arr[largest].height)
            largest = l;

        if (r < n && arr[r].height > arr[largest].height)
            largest = r;

        if (largest != i) {
            Player swap = arr[i];
            arr[i] = arr[largest];
            arr[largest] = swap;

            heapify(arr, n, largest);
        }
    }

    public static void main(String[] args) {
        try {
            File logFile = new File("808360_heapsort.txt");
            FileWriter logWriter = new FileWriter(logFile);
            int comparisons = 0;
            int swaps = 0;

            // Reading the CSV file
            List<Player> players = new ArrayList<>();
            File file = new File("/tmp/players.csv");
            Scanner scanner = new Scanner(file);
            scanner.nextLine(); // skipping the header

            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String[] attributes = line.split(",");
                Player player = new Player(
                        Integer.parseInt(attributes[0]),
                        attributes[1],
                        Integer.parseInt(attributes[2]),
                        Integer.parseInt(attributes[3]),
                        attributes[4],
                        attributes[5],
                        attributes[6],
                        attributes[7]
                );
                players.add(player);
            }
            scanner.close();

            // Sorting using heapsort
            Player[] playerArray = players.toArray(new Player[0]);
            long startTime = System.currentTimeMillis();
            heapSort(playerArray);
            long endTime = System.currentTimeMillis();
            long executionTime = endTime - startTime;

            // Writing to the log file
            logWriter.write("808360\t" + comparisons + "\t" + swaps + "\t" + executionTime + "\n");

            // Reading player IDs from input
            Scanner inputScanner = new Scanner(System.in);
            String input = "";
            while (!input.equals("FIM")) {
                input = inputScanner.next();
                if (input.equals("FIM")) break;
                int id = Integer.parseInt(input);
                for (Player p : playerArray) {
                    if (p.id == id) {
                        System.out.println(p.toString());
                    }
                }
            }
            inputScanner.close();
            logWriter.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
