import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;

class Player {
    int id;
    String playerName;
    int height;
    int weight;
    String born;
    String college;
    String birthCity;
    String birthState;

    public Player(int id, String playerName, int height, int weight, String born, String college, String birthCity, String birthState) {
        this.id = id;
        this.playerName = playerName;
        this.height = height;
        this.weight = weight;
        this.born = born;
        this.college = college;
        this.birthCity = birthCity;
        this.birthState = birthState;
    }

    @Override
    public String toString() {
        return "[Id: " + id + " Player: " + playerName + " height: " + height + " weight: " + weight + " born: " + born
                + " collage: " + college + " birth city: " + birthCity + " birth state: " + birthState + "]";
    }
}

public class PlayerMergeSort {
    static int comparisons = 0;
    static int movements = 0;

    public static void mergeSort(Player[] arr, int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            merge(arr, l, m, r);
        }
    }

    public static void merge(Player[] arr, int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;

        Player[] L = new Player[n1];
        Player[] R = new Player[n2];

        for (int i = 0; i < n1; ++i) {
            L[i] = arr[l + i];
        }
        for (int j = 0; j < n2; ++j) {
            R[j] = arr[m + 1 + j];
        }

        int i = 0, j = 0;
        int k = l;
        while (i < n1 && j < n2) {
            if (L[i].college.compareTo(R[j].college) <= 0) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
            comparisons++;
            movements++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
            movements++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
            movements++;
        }
    }

    public static void writeLog(int comparisons, int movements, double timeTaken) {
        try {
            FileWriter logFile = new FileWriter("808360_mergesort.txt");
            logFile.write("808360\t" + comparisons + "\t" + movements + "\t" + timeTaken);
            logFile.close();
        } catch (IOException e) {
            System.out.println("An error occurred while writing the log file.");
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        String filePath = "/tmp/players.csv";
        String line;
        int maxPlayers = 3922;
        Player[] players = new Player[maxPlayers];
        int count = 0;

        try {
            BufferedReader br = new BufferedReader(new FileReader(filePath));
            while ((line = br.readLine()) != null) {
                String[] data = line.split(",");
                Player player = new Player(Integer.parseInt(data[0]), data[1], Integer.parseInt(data[2]),
                        Integer.parseInt(data[3]), data[4], data[5], data[6], data[7]);
                players[count] = player;
                count++;
            }
            br.close();
        } catch (IOException e) {
            System.out.println("An error occurred while reading the file.");
            e.printStackTrace();
        }

        long startTime = System.nanoTime();
        mergeSort(players, 0, count - 1);
        long endTime = System.nanoTime();
        double timeTaken = (endTime - startTime) / 1e6; 

        writeLog(comparisons, movements, timeTaken);

        for (int i = 0; i < count; i++) {
            System.out.println(players[i]);
        }
    }
}
