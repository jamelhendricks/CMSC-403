import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.layout.BorderPane;
import javafx.scene.control.ProgressBar;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;


public class RaceTrack extends Application {

	int numCars;
	int carLength = 32;
	int trackLength = 400;
	int finishLine = trackLength-carLength;
	boolean winner = false;

	Stage stage;
	ImageView[] carViews;


	/*

		

	*/

	
	public void initStage(Stage stage){
		stage.setX(500);
		stage.setY(500);

		stage.setMinHeight(200);
		stage.setMinWidth(500);
		stage.setResizable(false);

		Button startbt = new Button();
		Button pausebt = new Button();
		Button resetbt = new Button();
		
		startbt.setText("Start");
		pausebt.setText("Pause");
		resetbt.setText("Reset");

		startbt.setOnAction(new EventHandler<ActionEvent>() {
		    @Override public void handle(ActionEvent e) {
				startRace();
		    }
		});

		HBox btbox = new HBox();
		btbox.getChildren().addAll(startbt, pausebt, resetbt);
		btbox.setPadding(new Insets(12.5, 0, 12.5, 0));
		btbox.setSpacing(100);
		btbox.setAlignment(Pos.CENTER);

		VBox raceContainer = new VBox();
		raceContainer.setSpacing(10);
		Image carImg = new Image("sportive-car.png");

		carViews = new ImageView[numCars];
		HBox[] tracks = new HBox[numCars];


		for (int i = 0; i < numCars; i++){
			ImageView carFrame = new ImageView(carImg);
			HBox carTrack = new HBox();
			
			// set car starting spot
			carFrame.setTranslateX((-1) * carLength);

			carTrack.setTranslateX(50);
			carTrack.setMaxWidth(trackLength);
			//carTrack.setMaxHeight(16);
			carTrack.setStyle("-fx-background-color: #CCCCCC"); 
			carTrack.getChildren().add(carFrame);

			raceContainer.getChildren().add(carTrack);

			carViews[i] = carFrame;
			tracks[i] = carTrack;

		}

		BorderPane pane = new BorderPane();
		pane.setTop(btbox);
		pane.setCenter(raceContainer);
		
		Scene scene = new Scene(pane);
		stage.setScene(scene);
	}

	public void moveCar(int carIndex, int position){

		Thread t = new Thread( () -> {

			if(winner){
				return;
			} 

			carViews[carIndex].setTranslateX(position);
			if(position >= finishLine) {
				alertWinner(carIndex);
			}

		});
		Platform.runLater(t);
		
	}

	public void alertWinner(int carIndex){
		/* TO DO: alert winner */
		/***********************/
		
		winner = true;
		System.out.println("Winner: Car #" + (carIndex + 1));
	}

	public void startRace(){

		for (int i = 0; i < numCars; i++){
			CarThread t = new CarThread(this, i);
			t.start();
		}

	}


	public void start(Stage stage) {

		this.numCars = 3;
		initStage(stage);
		stage.show();	
	}


	public static void main(String[] args){
		launch(args);
	}
}