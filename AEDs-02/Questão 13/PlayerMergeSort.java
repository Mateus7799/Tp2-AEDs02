import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

class Player {
    int id;
    String playerName;
    int height;
    int weight;
    String born;
    String college;
    String birthCity;
    String birthState;

    public Player(int id, String playerName, int height, int weight, String born, String college, String birthCity,
            String birthState) {
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
    }

    public static void merge(Player[] arr, int l, int m, int r) {
    }

    public static void writeLog(int comparisons, int movements, double timeTaken) {
    }

    public static void main(String[] args) {
        String filePath = "/tmp/players.csv";
        String line;
        int maxPlayers = 3922;
        Player[] players = new Player[maxPlayers];
        int count = 0;

        try {
            BufferedReader br = new BufferedReader(new FileReader(filePath));

            br.readLine();
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

        for (int i = 0; i < count; i++) {
            System.out.println(players[i]);
        }
    }
}
