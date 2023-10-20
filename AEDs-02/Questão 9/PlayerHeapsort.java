import java.io.*;
import java.util.*;

class Player {
    int id;
    String name;
    int height;
    int weight;
    String collage;
    String born;
    String birthCity;
    String birthState;

    public Player(int id, String name, int height, int weight, String collage, String born, String birthCity, String birthState) {
        this.id = id;
        this.name = name;
        this.height = height;
        this.weight = weight;
        this.collage = collage;
        this.born = born;
        this.birthCity = birthCity;
        this.birthState = birthState;
    }

    public String toString() {
        return "[" + id + " ## " + name + " ## " + height + " ## " + weight + " ## " + born + " ## " + collage + " ## " + birthCity + " ## " + birthState + "]";
    }
}

public class PlayerHeapsort {
    private static int comparisons = 0;
    private static int movements = 0;

    private static void heapify(Player[] arr, int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && arr[l].height > arr[largest].height) {
            largest = l;
        }

        if (r < n && arr[r].height > arr[largest].height) {
            largest = r;
        }

        if (largest != i) {
            Player temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;
            movements += 3;

            heapify(arr, n, largest);
        }
    }

    private static void heapSort(Player[] arr) {
        int n = arr.length;

        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }

        for (int i = n - 1; i > 0; i--) {
            Player temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            movements += 3;

            heapify(arr, i, 0);
        }
    }

    public static void main(String[] args) {
        try {
            BufferedReader reader = new BufferedReader(new FileReader("/tmp/players.csv"));
            List<Player> players = new ArrayList<>();

            String line = reader.readLine(); // read header line and discard
            while ((line = reader.readLine()) != null) {
                String[] attributes = line.split(",");
                Player player = new Player(Integer.parseInt(attributes[0].trim()), attributes[1].trim(), Integer.parseInt(attributes[2].trim()), Integer.parseInt(attributes[3].trim()), attributes[4].trim(), attributes[5].trim(), attributes[6].trim(), attributes[7].trim());
                players.add(player);
            }
            reader.close();

            Scanner scanner = new Scanner(System.in);
            List<Player> selectedPlayers = new ArrayList<>();
            System.out.println("Enter player IDs (type 'FIM' to finish):");
            while (true) {
                String input = scanner.nextLine();
                if (input.equals("FIM")) {
                    break;
                }
                int id = Integer.parseInt(input.trim());
                for (Player player : players) {
                    if (player.id == id) {
                        selectedPlayers.add(player);
                        break;
                    }
                }
            }
            scanner.close();

            Player[] arr = selectedPlayers.toArray(new Player[0]);
            long startTime = System.nanoTime();
            heapSort(arr);
            long endTime = System.nanoTime();
            long duration = (endTime - startTime);

            PrintWriter writer = new PrintWriter("808360_heapsort.txt", "UTF-8");
            writer.println("808360\t" + comparisons + "\t" + movements + "\t" + duration);
            writer.close();

            for (Player player : arr) {
                System.out.println(player.toString());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
