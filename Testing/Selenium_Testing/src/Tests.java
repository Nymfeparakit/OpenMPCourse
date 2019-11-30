import org.junit.Assert;
import org.junit.Test;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.openqa.selenium.By;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.chrome.ChromeOptions;
import org.openqa.selenium.firefox.FirefoxDriver;

public class Tests {

    ChromeDriver driver;

    public Tests() {
        System.setProperty("webdriver.chrome.driver", "chromedriver_win32\\chromedriver.exe");
        driver = new ChromeDriver();
    }

    /*
    private void login() {

        WebElement githubLogin = driver.findElement(By.xpath("//button[@class='grid--cell s-btn s-btn__icon s-btn__github bar-md ba bc-black-3']"));
        githubLogin.click();
        WebElement loginField = driver.findElement(By.xpath("//input[@id='login_field']"));
        loginField.sendKeys("maxlex047@gmail.com");
        WebElement passwordField = driver.findElement(By.xpath("//input[@id='password']"));
        passwordField.sendKeys("ugft7et8");
        passwordField.submit();

    }

    @Test
    public void fillOutRegistrationFormAndSubmit_ShouldRegister() {

        driver.get("https://ru.stackoverflow.com/users/signup?ssrc=head&returnurl=https%3a%2f%2fru.stackoverflow.com%2f");

        WebElement elUsernameInput = driver.findElement(By.xpath("//input[@id='display-name']"));
        elUsernameInput.sendKeys("sasha");
        sleep(2000);
        WebElement elEmailInput = driver.findElement(By.xpath("//input[@name='email']"));
        String mail = "sasha@mail.ru";
        elEmailInput.sendKeys(mail);
        sleep(2000);
        WebElement elPasswordInput = driver.findElement(By.xpath("//input[@name='password']"));
        elPasswordInput.sendKeys("1235678910aa");
        sleep(2000);
        elPasswordInput.submit();
        sleep(2000);
        WebElement successText = driver.findElement(By.xpath("//div[@class='rid--cell fs-body3 mb8']"));
        Assert.assertEquals("Registration email sent to " + mail + ". Open this email to finish signup.",
                successText.getText());
        driver.quit();


    }
    */

    @Test
    public void fillOutRegistrationFormAndSubmit_ShouldRegister() {

        String nameStr = "tomsmith";
        String passwordStr = "SuperSecretPassword!";

        driver.get("http://the-internet.herokuapp.com/login");
        WebElement name = driver.findElement(By.xpath("//input[@name='username']"));
        name.sendKeys(nameStr);
        sleep(2000);
        WebElement password = driver.findElement(By.xpath("//input[@type='password']"));
        password.sendKeys(passwordStr);
        sleep(2000);
        password.submit();
        sleep(2000);

        //WebElement textSuccess = driver.findElement(By.xpath("//div[@id='flash']"));
        WebElement textSuccess = driver.findElement(By.xpath("//h4[@class='subheader']"));
        Assert.assertEquals("Welcome to the Secure Area. When you are done click logout below.", textSuccess.getText());
        sleep(2000);

        /*driver.get("http://thedemosite.co.uk/login.php");
        name = driver.findElement(By.xpath("//input[@NAME='username']"));
        name.sendKeys(nameStr);
        sleep(2000);
        password = driver.findElement(By.xpath("//input[@type='password']"));
        password.sendKeys(passwordStr);
        sleep(2000);
        password.submit();*/



    }

    private void sleep(int millis) {
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    /*
    @Test
    public void enterExactQuoteInSearch_ShouldFindExactBlog() {

        driver.get("https://ru.stackoverflow.com/");

        WebElement searchInput = driver.findElement(By.xpath("//input[@name='q']"));
        String inputStr  = "Рендер туманности";
        searchInput.sendKeys("\"" + inputStr + "\"\n");
        sleep(2000);
        WebElement searchResult = driver.findElement(By.xpath("//div[@class='question-summary search-result']//a"));
        Assert.assertEquals(searchResult.getText(), "В: " + inputStr);
        sleep(2000);

        driver.quit();

    }

    @Test
    public void enterUserAndPostScore_ShouldFindPostsOfUserWithSetScore() {

        driver.get("https://stackoverflow.com/");

        WebElement searchInput = driver.findElement(By.xpath("//input[@name='q']"));
        String inputStr  = "user:1144035 score:300..";
        searchInput.sendKeys(inputStr + "\n");
        sleep(2000);
        WebElement searchResult = driver.findElement(By.xpath("//div[@class='question-summary search-result']//a"));
        Assert.assertEquals(searchResult.getText(), "A: How do I put an 'if clause' in an SQL string?");
        sleep(2000);

        driver.quit();


    }

    private void addOrRemoveFavorites() {

        driver.get("https://stackoverflow.com/users/login?ssrc=head&returnurl=https%3a%2f%2fstackoverflow.com%2fquestions%2f16347649%2fsql-between-not-inclusive%2f16347680");
        login();
        WebElement favoriteBtn = driver.findElement(By.xpath("//button[@class='js-favorite-btn s-btn s-btn__unset c-pointer py4 js-gps-track']"));
        favoriteBtn.click();
        sleep(2000);

    }


    @Test
    public void addPostToFavorite_ShouldIncreaseFavoritesCounter() {

        addOrRemoveFavorites();
        WebElement favoriteCountLbl = driver.findElement(By.xpath("//div[@class='js-favorite-count mt4']"));
        String favoriteCount = favoriteCountLbl.getText();
        String newFavoriteCount = Integer.toString(Integer.parseInt(favoriteCount) + 1);

        Assert.assertEquals(favoriteCountLbl.getText(), newFavoriteCount);

        addOrRemoveFavorites();

        driver.quit();

    }


    @Test
    public void searchPostsInFavorites_SearchResultsShouldContainSpecificPost() {

        //addOrRemoveFavorites();

        driver.get("https://stackoverflow.com/");
        WebElement searchInput = driver.findElement(By.xpath("//input[@name='q']"));
        String inputStr  = "infavorites:12424123";
        searchInput.sendKeys(inputStr + "\n");
        sleep(2000);
        WebElement searchResult = driver.findElement(By.xpath("//div[@class='question-summary search-result']//a"));

        Assert.assertEquals(searchResult.getText(), "Q: SQL “between” not inclusive");
        sleep(2000);

        //addOrRemoveFavorites();

        driver.quit();

    }

    @Test
    public void enterIncorrectPasswordInLoginForm_ShouldPrintErrorMessage() {

        driver.get("https://stackoverflow.com/users/login?ssrc=head");
        WebElement emailField = driver.findElement(By.xpath("//input[@id='email']"));
        emailField.sendKeys("maxlex047@gmail.com");
        sleep(2000);
        WebElement passwordField = driver.findElement(By.xpath("//input[@id='password']"));
        passwordField.sendKeys("123");
        sleep(2000);
        passwordField.submit();
        WebElement errorText = driver.findElement(By.xpath("//p[@class='grid--cell s-input-message js-error-message ']"));
        Assert.assertEquals("The email or password is incorrect.", errorText.getText());
        sleep(2000);

        driver.quit();

    }
        */

}