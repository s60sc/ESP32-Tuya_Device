      // websocket handling
      let wsServer = "ws://" + document.location.host + ":83/ws";
      let ws;
      
      window.addEventListener('load', onLoad);

      function onLoad(event) {
        initWebSocket();
      }
      
      // define websocket handling
      function initWebSocket() {
        add_log_line("Connect to: " + wsServer);
        ws = new WebSocket(wsServer);
        ws.onopen = onOpen;
        ws.onclose = onClose;
        ws.onmessage = onMessage; 
      }

      // add received line to log element
      function add_log_line(text) {
        let log = document.getElementById('log');
        let new_node = document.createTextNode(text + "\n");
        log.append(new_node);
      }

      // connect to websocket server
      function onOpen(event) {
        add_log_line("Connected");
      }
      
      // process received message
      function onMessage(messageEvent) {
        add_log_line(messageEvent.data);
      }
      
      function onClose(event) {
        add_log_line("Disconnected");
        initWebSocket();
      }

      // process message to send
      function sendCmd() {
        // send user command to websocket server
        let txt  = document.getElementById('txtCmd');
        let line = txt.value;
        if (line != "") {
          ws.send(line);
          add_log_line("CMD: " + line);
          txt.value = "";
          txt.focus();
        }
        return false;
      }