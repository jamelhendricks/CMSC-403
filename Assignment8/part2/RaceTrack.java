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

public class RaceTrack extends Application {

	int numCars;
	Stage stage;

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

		HBox btbox = new HBox();
		btbox.getChildren().addAll(startbt, pausebt, resetbt);
		btbox.setPadding(new Insets(12.5, 0, 12.5, 0));
		btbox.setSpacing(100);
		btbox.setAlignment(Pos.CENTER);

		VBox raceContainer = new VBox();
		raceContainer.setSpacing(10);
		Image carImg = new Image("sportive-car.png");

		ImageView[] carViews = new ImageView[numCars];
		HBox[] tracks = new HBox[numCars];


		for (int i = 0; i < numCars; i++){
			ImageView carFrame = new ImageView(carImg);
			HBox carTrack = new HBox();
			
			// set car starting spot
			carFrame.setTranslateX(-32);

			carTrack.setTranslateX(50);
			carTrack.setMaxWidth(400);
			carTrack.setMaxHeight(16);
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


	public void start(Stage stage) {
		/*
		stage.setX(500);
		stage.setY(500);

		stage.setMinHeight(200);
		stage.setMinWidth(500);
		stage.setResizable(false);
		
		BorderPane pane = new BorderPane();		
		Scene scene = new Scene(pane);
		stage.setScene(scene);
		*/
		this.numCars = 3;
		initStage(stage);
		stage.show();	

	}


	public static void main(String[] args){
		launch(args);
	}
}