#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

const std::string htmlContent = R"html(
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="icon" type="" href="https://th.bing.com/th/id/R.aa2f82ccbfb41fa729a63bec476d3852?rik=bOknz3cHUoueCw&riu=http%3a%2f%2fwww.education-defense.fr%2fIMG%2farton469.png%3f1523775967&ehk=7BbKsLbagS6T0uGUo0oJS0X9hP%2fYJj%2b1EHPa3s8rSGo%3d&risl=&pid=ImgRaw&r=0">
    <title>Contrôle des Cibles - Gendarmerie</title>
    <style>
        :root {
            --primary-color: #0B3D92;
            --primary-hover: #000000;
            --secondary-color: #D8D9DB;
            --background-color: #D8D9DB;
            --text-color: #000000;
            --accent-color: #F7D24C;
            --border-radius: 8px;
            --box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
            --transition: all 0.3s ease;
        }

        body {
            background: linear-gradient(135deg, var(--background-color) 0%, #ffffff 100%);
            font-family: 'Roboto', sans-serif;
            color: var(--text-color);
            margin: 0;
            padding: 20px;
            display: flex;
            flex-direction: column;
            align-items: center;
            min-height: 100vh;
            line-height: 1.6;
        }
        h1 {
            color: var(--primary-color);
            font-weight: 300;
            margin-bottom: 10px;
            text-align: center;
        }
        h2 {
            color: var(--text-color);
            font-weight: 400;
            margin-top: 30px;
            margin-bottom: 15px;
            text-align: center;
        }
        p {
            font-size: 18px;
            text-align: center;
            margin-bottom: 20px;
        }
        button {
            background-color: var(--primary-color);
            color: white;
            border: none;
            padding: 12px 24px;
            margin: 5px;
            cursor: pointer;
            font-size: 16px;
            border-radius: var(--border-radius);
            box-shadow: var(--box-shadow);
            transition: var(--transition);
        }
        button:hover {
            background-color: var(--primary-hover);
            transform: translateY(-2px);
            box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);
        }
        form {
            background: white;
            padding: 20px;
            border-radius: var(--border-radius);
            box-shadow: var(--box-shadow);
            margin-bottom: 20px;
            width: 100%;
            max-width: 400px;
        }
        div {
            margin-bottom: 20px;
        }
        label {
            cursor: pointer;
            margin-right: 10px;
        }
        input[type="radio"], input[type="number"], input[type="range"] {
            margin-right: 5px;
        }
        input[type="range"] {
            -webkit-appearance: none;
            appearance: none;
            width: 100%;
            height: 6px;
            background: #ddd;
            outline: none;
            border-radius: 3px;
        }
        input[type="range"]::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 20px;
            height: 20px;
            background: var(--primary-color);
            border-radius: 50%;
            cursor: pointer;
        }
        input[type="range"]::-moz-range-thumb {
            width: 20px;
            height: 20px;
            background: var(--primary-color);
            border-radius: 50%;
            cursor: pointer;
            border: none;
        }
        input[type="number"] {
            padding: 8px 12px;
            border: 1px solid #ccc;
            border-radius: var(--border-radius);
            font-size: 16px;
            background: white;
            transition: var(--transition);
        }
        input[type="number"]:focus {
            outline: none;
            border-color: var(--primary-color);
            box-shadow: 0 0 0 2px rgba(0, 123, 255, 0.25);
        }
        input[type="radio"] {
            display: none;
        }
        label[for="normal"], label[for="reflexe"] {
            display: inline-block;
            background-color: var(--secondary-color);
            color: white;
            padding: 10px 20px;
            margin: 5px;
            border-radius: var(--border-radius);
            cursor: pointer;
            transition: var(--transition);
            box-shadow: var(--box-shadow);
        }
        label[for="normal"]:hover, label[for="reflexe"]:hover {
            background-color: var(--accent-color);
            transform: translateY(-2px);
            box-shadow: 0 6px 8px rgba(0, 0, 0, 0.15);
        }
        input[type="radio"]:checked + label {
            background-color: var(--primary-color);
        }
        input[type="radio"]:checked + label:hover {
            background-color: var(--primary-hover);
        }
        .cible {
            display: inline-block;
            width: 150px;
            height: 150px;
            min-width: 80px;
            min-height: 80px;
            max-width: 120px;
            max-height: 120px;
            border-radius: 50%;
            background: radial-gradient(circle, #dc3545 0% 50%, #ffffff 50% 70%, #000000 70% 90%, #ffffff 90% 100%);
            cursor: pointer;
            position: relative;
            margin: 10px;
            transition: var(--transition);
            box-shadow: var(--box-shadow);
        }
        .cible input {
            display: none;
        }
        .cible span {
            position: absolute;
            bottom: -20px;
            left: 50%;
            transform: translateX(-50%);
            font-size: 12px;
            color: #333;
        }
        .cible.selected {
            background: radial-gradient(circle, var(--primary-color) 0% 50%, white 50% 70%, black 70% 90%, white 90% 100%);
        }
        .cible:hover {
            transform: scale(1.05);
        }
        .cibles-container {
            display: flex;
            justify-content: center;
            flex-wrap: wrap;
            margin-bottom: 30px;
        }
        .progress-bar {
            position: absolute;
            bottom: 0;
            left: 0;
            width: 100%;
            height: 4px;
            background: var(--primary-color);
            transform: scaleX(0);
            transform-origin: left;
            transition: transform 0.3s ease;
        }
        .progress-bar.active {
            transform: scaleX(1);
        }
    </style>
</head>
<body>
    <img src="http://www.education-defense.fr/IMG/arton469.png?1523775967" alt="Logo PSIG" style="width: 100px; height: auto; margin-bottom: 10px;">
    <h1>Contrôle des Cibles - Gendarmerie</h1>
    <p>Voici la maquette du site avec une adaptation pour chaque appareils.</p>

    <h2>Contrôle des Cibles</h2>
    <label for="cible1" class="cible">
        <input type="checkbox" id="cible1" name="cible1">
        <span>Cible 1</span>
        <div class="progress-bar"></div>
    </label>
    <label for="cible2" class="cible">
        <input type="checkbox" id="cible2" name="cible2">
        <span>Cible 2</span>
        <div class="progress-bar"></div>
    </label>
    <label for="cible3" class="cible">
        <input type="checkbox" id="cible3" name="cible3">
        <span>Cible 3</span>
        <div class="progress-bar"></div>
    </label>
    <label for="cible4" class="cible">
        <input type="checkbox" id="cible4" name="cible4">
        <span>Cible 4</span>
        <div class="progress-bar"></div>
    </label>

    <h2>Mode de fonctionnement</h2>
    <form>
        <input type="radio" id="normal" name="mode" value="normal" checked>
        <label for="normal">Mode Normal</label><br>
        <input type="radio" id="reflexe" name="mode" value="reflexe">
        <label for="reflexe">Mode Réflexe</label><br><br>
        <div id="reflexe-options" style="display: none;">
            <input type="range" id="delay" name="delay" min="0.1" max="10" step="0.1" value="2">
            <label for="delay">Délai (secondes) :</label>
            <input type="number" id="delay-value" min="0.1" max="10" step="0.1" value="2" style="width: 70px; margin-left: 15px;">
        </div>
    </form>

    <br>
    <button id="launch-script">Lancer le Script</button>
    <button id="stop-script">Stopper le Script</button>

    <script>
        document.addEventListener('DOMContentLoaded', function() {
            const modeRadios = document.querySelectorAll('input[name="mode"]');
            const reflexeOptions = document.getElementById('reflexe-options');
            const delaySlider = document.getElementById('delay');
            const delayValue = document.getElementById('delay-value');
            const checkboxes = document.querySelectorAll('input[name^="cible"]');
            const launchButton = document.getElementById('launch-script');
            const stopButton = document.getElementById('stop-script');
            let timers = []; // Array to hold active timers

            // Sync slider and number input
            delaySlider.addEventListener('input', function() {
                delayValue.value = this.value;
            });
            delayValue.addEventListener('input', function() {
                delaySlider.value = this.value;
            });

            // Show/hide delay field based on mode
            modeRadios.forEach(radio => {
                radio.addEventListener('change', function() {
                    if (this.value === 'reflexe') {
                        reflexeOptions.style.display = 'block';
                    } else {
                        reflexeOptions.style.display = 'none';
                    }
                });
            });

            // Handle checkbox changes
            checkboxes.forEach(checkbox => {
                checkbox.addEventListener('change', function() {
                    const label = this.parentElement;
                    const progressBar = label.querySelector('.progress-bar');
                    const isReflexe = document.getElementById('reflexe').checked;
            const delay = parseFloat(delaySlider.value) * 1000; // Convert to milliseconds

                    if (this.checked) {
                        label.classList.add('selected');
                        progressBar.style.transform = 'scaleX(0)';
                        progressBar.classList.remove('active');
                    } else {
                        label.classList.remove('selected');
                        if (isReflexe) {
                            // Start progress bar animation
                            progressBar.style.transitionDuration = delay + 'ms';
                            progressBar.classList.add('active');
                            // In reflex mode, re-enable after delay
                            const timer = setTimeout(() => {
                                this.checked = true;
                                label.classList.add('selected');
                                progressBar.style.transform = 'scaleX(0)';
                                progressBar.classList.remove('active');
                            }, delay);
                            timers.push(timer);
                        }
                    }
                });
            });

            // Stop button functionality
            stopButton.addEventListener('click', function() {
                // Clear all active timers
                timers.forEach(timer => clearTimeout(timer));
                timers = [];
                // Reset all checkboxes and progress bars
                checkboxes.forEach(checkbox => {
                    checkbox.checked = false;
                    const label = checkbox.parentElement;
                    label.classList.remove('selected');
                    const progressBar = label.querySelector('.progress-bar');
                    progressBar.style.transform = 'scaleX(0)';
                    progressBar.classList.remove('active');
                });
            });

            // Launch button functionality (placeholder)
            launchButton.addEventListener('click', function() {
                // Add launch script logic here if needed
                console.log('Script launched');
            });
        });
    </script>
</body>
</html>
)html";

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed" << std::endl;
            continue;
        }

        char buffer[1024];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            std::string request(buffer, bytesReceived);
            std::cout << "Request: " << request << std::endl;

            // Simple routing: serve index.html for root
            std::string response;
            if (request.find("GET / ") != std::string::npos || request.find("GET /index.html") != std::string::npos) {
                response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + htmlContent;
            } else {
                response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nPage not found";
            }

            send(clientSocket, response.c_str(), response.size(), 0);
        }

        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
