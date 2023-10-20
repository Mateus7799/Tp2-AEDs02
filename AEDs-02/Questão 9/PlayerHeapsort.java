import java.io.*;
import java.util.*;

class Player {
    int id;
    String player;
    int height;
    int weight;
    String born;
    String collage;
    String birthCity;
    String birthState;

    public Player(int id, String player, int height, int weight, String born, String collage, String birthCity, String birthState) {
        this.id = id;
        this.player = player;
        this.height = height;
        this.weight = weight;
        this.born = born;
        this.collage = collage;
        this.birthCity = birthCity;
        this.birthState = birthState;
    }

    @Override
    public String toString() {
        return "[" + id + " ## " + player + " ## " + height + " ## " + weight + " ## " + born + " ## " + collage + " ## " + birthCity + " ## " + birthState + "]";
    }
}

public class PlayerHeapsort {
    static int comparisons = 0;
    static int movements = 0;

    public static void heapify(Player[] arr, int n, int i) {
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

    public static void heapSort(Player[] arr) {
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
            File file = new File("/tmp/players.csv");
            Scanner sc = new Scanner(file);

            ArrayList<Player> players = new ArrayList<>();

            if (sc.hasNextLine()) {
                sc.nextLine();
            }

            while (sc.hasNextLine()) {
                String[] data = sc.nextLine().split(",");
                int id = Integer.parseInt(data[0].trim());
                String player = data[1].trim();
                int height = Integer.parseInt(data[2].trim());
                int weight = Integer.parseInt(data[3].trim());
                String collage = data[4].trim();
                String born = data[5].trim();
                String birthCity = data[6].trim();
                String birthState = data[7].trim();

                players.add(new Player(id, player, height, weight, born, collage, birthCity, birthState));
            }
            sc.close();

            Scanner inputScanner = new Scanner(System.in);

            ArrayList<Integer> ids = new ArrayList<>();
            while (true) {
                String input = inputScanner.nextLine();
                if (input.equals("FIM")) {
                    break;
                }
                ids.add(Integer.parseInt(input));
            }
            inputScanner.close();

            Player[] selectedPlayers = new Player[ids.size()];
            int idx = 0;
            for (Player p : players) {
                if (ids.contains(p.id)) {
                    selectedPlayers[idx] = p;
                    idx++;
                }
            }

            heapSort(selectedPlayers);

            for (Player p : selectedPlayers) {
                System.out.println(p.toString());
            }

            FileWriter logFile = new FileWriter("808360_heapsort.txt");
            logFile.write("808360\t" + comparisons + "\t" + movements + "\t" + "TimeTaken" + "\n");
            logFile.close();

        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        } catch (IOException e) {
            System.out.println("An error occurred while writing the log file.");
            e.printStackTrace();
        }
    }
}
