# Run Almalinux9 with Docker on MAC
The following guide was written for a macOS <ins>Sonoma 14.7.1</ins> with <ins>Intel Core i5 dual-core</ins>.

## Install Docker on macOS 

1. Go to https://docs.docker.com/desktop/setup/install/mac-install/.

2. Identify the **Docker Desktop** version that matches the type of **Chip** on your computer. 

    ![./images/dockersite.png](./images/dockersite.png)

    In order to find out if your MAC has <ins>Apple Silicon</ins> or <ins>Intel Chip</ins>:

    - Click the **Apple**  icon in the top-left corner of your screen.
    - Select **About this Mac**.
    - Read which type of **Chip** is used on your computer.

        <img src="./images/chip.png" alt="chip" style="width:400px;"/>

3. Once identified, download the proper `Docker.dmg` file. 

4. Go to **Finder>Download** and double click on the `Docker.dmg` file, then drag and drop the **Docker** icon into the **Applications** folder.
    
    <br/>
    
    ![draganddrop](./images/draganddrop.png)

    <br/>

<br/>

5. Once the installation is ready, the **Docker** app will be available in the **Applications** folder. 


6. Click on the icon to start the application: the **Docker's GUI** will open.


7. If you want, you can verify that your installation worked properly by running the following command on a **Terminal** window:
    ```
    docker --version
    ```

8. By default, **Docker Desktop** will run in the background after closing the GUI's window, but you can always check the applications's status by the menu bar in the top-right corner of your screen.

9. If you want to quit it you can click on **Quit Docker Desktop**; if you want to open the GUI again, you can click on **Go to the Dashboard**.


## Download Almalinux 9 

1. Open a **Terminal** window.

2. Run the following command  on terminal to download the Almalinux 9 image: 
    ```
    docker pull almalinux:9
    ```
    and verify that the output is similar to this:
    
    ```
    9: Pulling from library/almalinux
    e60c9fe2676d: Download complete 
    Digest: sha256:6d78b43b103e7ca90c43a790e73bdd421cec5ae0269b6051ef6836f4070b7476
    Status: Downloaded newer image for almalinux:9
    docker.io/library/almalinux:9
    ```

    From the Docker's GUI, in the Image section, you will see that a new image appeared: 

    ![image.png](./images/dockerimage.png)

2. Once you have downloaded the image, start  a new container by running:

    ```
    docker run -it almalinux:9 /bin/bash
    ```` 

    This will drop you into a bash shell inside the running container, where you can check that you are using the correct OS by running:
    
    ```
    cat /etc/os-release
    ``` 

    and verify that the output looks like this:

    ```
    NAME="AlmaLinux"
    VERSION="9.5 (Teal Serval)"
    ID="almalinux"
    ID_LIKE="rhel centos fedora"
    VERSION_ID="9.5"
    PLATFORM_ID="platform:el9"
    PRETTY_NAME="AlmaLinux 9.5 (Teal Serval)"
    ANSI_COLOR="0;34"
    LOGO="fedora-logo-icon"
    CPE_NAME="cpe:/o:almalinux:almalinux:9::baseos"
    HOME_URL="https://almalinux.org/"
    DOCUMENTATION_URL="https://wiki.almalinux.org/"
    BUG_REPORT_URL="https://bugs.almalinux.org/"
    ALMALINUX_MANTISBT_PROJECT="AlmaLinux-9"
    ALMALINUX_MANTISBT_PROJECT_VERSION="9.5"
    REDHAT_SUPPORT_PRODUCT="AlmaLinux"
    REDHAT_SUPPORT_PRODUCT_VERSION="9.5"
    SUPPORT_END=2032-06-01
    ```

4. You can exit the container wiht `exit` command.


### Conclusion
You now have Docker installed on your macOS, endowed with a container where Almalinux9 is running.





