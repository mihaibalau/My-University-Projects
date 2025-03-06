import Controller.Controller;
import GUI.AppFXController;
import GUI.SelectorFXController;
import Repository.IRepository;
import Repository.Repository;
import javafx.application.Application;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Group;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import javax.swing.*;
import java.awt.*;

public class MainFX extends Application {


    @Override
    public void start(Stage stage) throws Exception {
        IRepository repository = new Repository("logsGui.txt");
        Controller controller = new Controller(repository);

        FXMLLoader mainApp = new FXMLLoader();
        mainApp.setLocation(getClass().getResource("Resources/App.fxml"));
        mainApp.setControllerFactory(C -> new AppFXController(controller));
        Parent mainAppRoot = mainApp.load();
        AppFXController mainAppController = mainApp.getController();

        stage.setTitle("Toy Language by Balau Mihai");
        stage.setScene(new Scene(mainAppRoot));
        stage.show();

        Stage selectStage = new Stage();
        FXMLLoader setProgram = new FXMLLoader();
        setProgram.setLocation(getClass().getResource("Resources/Selector.fxml"));
        setProgram.setControllerFactory(c -> new SelectorFXController(controller, mainAppController));
        Parent setProgramWindowRoot = setProgram.load();

        selectStage.setTitle("Select Program");
        selectStage.setScene(new Scene(setProgramWindowRoot));
        selectStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
