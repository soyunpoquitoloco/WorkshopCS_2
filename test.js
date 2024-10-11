const connectButton = document.getElementById('connect-button');
const sendButton = document.getElementById('send-button');
const messageInput = document.getElementById('message-input');
const outputDiv = document.getElementById('output');
const sendButtonf = document.getElementById('send-button-frequency');
const frequencyInput = document.getElementById('frequency-input');
const outputUltra = document.getElementById('outputUltrasonic');
const outputHum = document.getElementById('outputHum');
const outputTemp = document.getElementById('outputTemp');
const outputLED = document.getElementById('outputLED');


let socket = null;
const domainName = '10.1.224.75'; // Remplacez par votre domaine ou votre service DDNS
  socket = new WebSocket(`ws://${domainName}`);

  socket.onopen = () => {
    console.log('Connexion établie');
    outputDiv.innerHTML += 'Connection established<br>';
  };

  socket.onmessage = (event) => {
    console.log(`Message reçu : ${event.data}`);
    if(event.data[0]=="d"){
      outputUltra.innerHTML = ` ${event.data.substr(1)}<br>`;
    }
    if(event.data[0]=="h"){
      outputHum.innerHTML = ` ${event.data.substr(1)}<br>`;
    }
    if(event.data[0]=="t"){
      outputTemp.innerHTML = ` ${event.data.substr(1)}<br>`;
    }
    if(event.data[0]=="f"){
      outputLED.innerHTML = ` ${event.data.substr(1)}<br>`;
    }
    if(event.data=="Message well received !"){
      outputDiv.innerHTML += `${event.data}<br>`;
    }
    //outputDiv.innerHTML += ` ${event.data}<br>`;
  };

  socket.onclose = () => {
    console.log('Connexion fermée');
    outputDiv.innerHTML += 'Connection closed<br>';
  };

  socket.onerror = (error) => {
    console.log(`Erreur : ${error}`);
    outputDiv.innerHTML += `Error : ${error}<br>`;
  };

sendButton.addEventListener('click', () => {
  const message = messageInput.value;
  socket.send(message);
  messageInput.value = '';
});

sendButtonf.addEventListener('click', () => {
  const message = "f" + frequencyInput.value;
  socket.send(message);
  frequencyInput.value = '';
});
