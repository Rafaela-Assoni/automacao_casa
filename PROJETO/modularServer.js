// file: modularServer.js

// modulos
var http = require('http')
var   fs = require('fs');

// porta
const port = 3000

// pagina principal
const mainPage = 'index.html'
const myStyle  = 'style.css'
const monitorar = 'monitorar.html'
const parametros = 'parametros.html'
const acao = 'acao.html'

var portTemp;

var a ="",b="",c ="",d="",e="",f="",g="",h="";
// servidor ouvindo em 'port'
var app = http.createServer(function(req, res) {
    
  var content = '';   // conteúdo da resposta
  var type = '';      // tipo da resposta: text/html, text/css
  
  if(req.url === '/') {   // requisição na raiz, carrega página principal
      content = fs.readFileSync(mainPage);      
      type = 'text/html';
  } if(req.url === '/monitorar.html'){
	  content = fs.readFileSync(monitorar);
	  type = 'text/html';
  } if(req.url === '/parametros.html'){
	  content = fs.readFileSync(parametros);
	  type = 'text/html';
  } if(req.url === '/acao.html'){
	  content = fs.readFileSync(acao);
	  type = 'text/html';
  }
  
  console.log(req.url) // tipo de requisição realizada
  res.writeHead(200, {'Content-Type': type}); // responde com tipo
  res.end(content + '\n'); // envia conteúdo 
}).listen(port)

var socket = require('socket.io').listen(app);

function controlePorta(){
  // : 03 02 01 0000 LRC
  var mensagem = ':' + '03' + '02' + '01' + '0000';
  var lrc = LRC(mensagem);
  mensagem = ':' + '03' + '02' + '01' + '0000' + lrc;
  sPort.write(mensagem);
}

socket.on('connection', function(client) {
	
  client.on('lampSala', function(data){ // LAMPADA SALA
      console.log('Recebido valor de lampada sala:' + data);
      slaveCmd = data[0]
      slaveState = data[1]
      mensagem = ':'+slaveCmd+slaveState // FORMA A MENSAGEM QUE VAI MANDAR PARA A SERIAL
      lrc = LRC(mensagem)
      //var msgfinal = mensagem+lrc // ADICIONA LRC A MENSAGEM
	  
    sPort.write(mensagem)
    console.log("Mensagem:" + mensagem)
  });
  
  
  client.on('lampQuarto', function(data){ // LAMPADA QUARTO
      console.log('Recebido valor de lampada quarto:' + data);
      slaveCmd = data[0]
      slaveState = data[1]
      mensagem = ':'+slaveCmd+slaveState // FORMA A MENSAGEM QUE VAI MANDAR PARA A SERIAL
      lrc = LRC(mensagem)
      //mensagem = ':'+slaveAdr+slaveCmd+slaveOut+slaveState+lrc // ADICIONA LRC A MENSAGEM
    sPort.write(mensagem)
    console.log("Mensagem:" + mensagem)
  });

  client.on('acaoAq', function(data){ // AQUECEDOR
      console.log('Recebido valor de Aquecedor quarto:' + data);
      slaveCmd = data[0]
      slaveState = data[1]
      mensagem = ':'+slaveCmd+slaveState // FORMA A MENSAGEM QUE VAI MANDAR PARA A SERIAL
      lrc = LRC(mensagem)
      //mensagem = ':'+slaveAdr+slaveCmd+slaveOut+slaveState+lrc // ADICIONA LRC A MENSAGEM
    sPort.write(mensagem)
    console.log("Mensagem:" + mensagem)
  });

  client.on('acaoAr', function(data){ // AR CONDICIONADO
      console.log('Recebido valor de Ar Condicionado sala:' + data);
      slaveCmd = data[0]
      slaveState = data[1]
      mensagem = ':'+slaveCmd+slaveState // FORMA A MENSAGEM QUE VAI MANDAR PARA A SERIAL
      lrc = LRC(mensagem)
      //mensagem = ':'+slaveAdr+slaveCmd+slaveOut+slaveState+lrc // ADICIONA LRC A MENSAGEM
    sPort.write(mensagem)
    console.log("Mensagem:" + mensagem)
  });
  
  client.on('a', function(data){ // DESLIGA ALARME 
        console.log('Valor recebido do HTML:' + data);
        slaveOut = data[0]
        slaveState = data[1]
        mensagem = ':'+slaveOut+slaveState // FORMA A MENSAGEM QUE VAI MANDAR PARA A SERIAL
        lrc = LRC(mensagem)
        //mensagem = ':'+slaveAdr+slaveOut+slaveState+lrc // ADICIONA LRC A MENSAGEM
    sPort.write(mensagem)
    console.log("Mensagem:" + mensagem)
  });

  client.on('acaoPorta', function(data){ // FECHA PORTA 
        console.log('Valor recebido do HTML:' + data);
        slaveOut = data[0]
        slaveState = data[1]
        mensagem = ':'+slaveOut+slaveState // FORMA A MENSAGEM QUE VAI MANDAR PARA A SERIAL
        lrc = LRC(mensagem)
        //mensagem = ':'+slaveAdr+slaveOut+slaveState+lrc // ADICIONA LRC A MENSAGEM
    sPort.write(mensagem)
    console.log("Mensagem:" + mensagem)
  });

  client.on('abrindoPorta', function(data){ // ABRE A PORTA 
        console.log('Valor recebido do HTML:' + data);
        slaveOut = data[0]
        slaveState = data[1]
        mensagem = ':'+slaveOut+slaveState // FORMA A MENSAGEM QUE VAI MANDAR PARA A SERIAL
        lrc = LRC(mensagem)
        //mensagem = ':'+slaveAdr+slaveOut+slaveState+lrc // ADICIONA LRC A MENSAGEM
    sPort.write(mensagem)
    console.log("Mensagem:" + mensagem)
  });

  client.on('comparaSenhaPorta', function(str1){ // COMPARA SENHA DA PORTA
    console.log("Parametro="+str1);
    console.log("Senha" +a);
    if (str1 == a)
    {        
        console.log("Abrindo Porta :01010000");
        socket.emit("ResSenha", true);
        //socket.emit("ResSenha", ['0'+ x,'FF00']);
        sPort.write(":01010000");
    }
    else
        socket.emit("ResSenha", false);
        

  });
  client.on('comparaSenhaAlarme', function(str1){ // COMPARA SENHA DO ALARME
    console.log("Parametro="+str1);
    console.log("Senha" +a);
    if (str1 == b)
    {        
        console.log("Abrindo Porta :01020000");
        socket.emit("ResSenha", true);
        //socket.emit("ResSenha", ['0'+ x,'FF00']);
        sPort.write(":01020000");
    }
    else
        socket.emit("ResSenha", false);
        

  });    
  
  client.on('cortina1', function(data){ // ABRE A PORTA 
    console.log('Valor recebido do HTML:' + data);
    slaveOut = data[0]
    slaveState = data[1]
    mensagem = ':'+slaveOut+slaveState // FORMA A MENSAGEM QUE VAI MANDAR PARA A SERIAL
    lrc = LRC(mensagem)
    //mensagem = ':'+slaveAdr+slaveOut+slaveState+lrc // ADICIONA LRC A MENSAGEM
sPort.write(mensagem)
console.log("Mensagem:" + mensagem)
});

client.on('cortina2', function(data){ // ABRE A PORTA 
  console.log('Valor recebido do HTML:' + data);
  slaveOut = data[0]
  slaveState = data[1]
  mensagem = ':'+slaveOut+slaveState // FORMA A MENSAGEM QUE VAI MANDAR PARA A SERIAL
  lrc = LRC(mensagem)
  //mensagem = ':'+slaveAdr+slaveOut+slaveState+lrc // ADICIONA LRC A MENSAGEM
sPort.write(mensagem)
console.log("Mensagem:" + mensagem)
});

  // ---------------------------------------------------------------------------------------------------
  
 
  client.on('config', function(data){ 
    a = data[0]
    b = data[1]
    c = data[2]
    d = data[3]
    e = data[4]
    f = data[5]
    g = data[6]
    h = data[7]

    //teste = new String(a)
    //console.log(teste);
    console.log(data);

    //socket.emit('parametros', [a, b, c, d, e, f, g, h])
        
  });

  client.on('configInicial', function(data){
    console.log(data);

    portTemp = data[4];

    if(data[6] < 10)
      slaveState = data[5] + '0' + data[6];
    else 
      slaveState = data[5] + data[6];

    slaveCmd = '01';

    mensagem = ':'+slaveAdr+slaveCmd+slaveOut+slaveState//":030501FF00";
    lrc = LRC(mensagem)
    mensagem = ':'+slaveAdr+slaveCmd+slaveOut+slaveState+lrc//":030501FF00lrc";
    console.log("Mensagem:" + mensagem);

    setInterval(controlePorta, portTemp*60000);

    sPort.write(mensagem);
  });

  client.on('atualizaTela', function(data)
  {
    console.log('Valor de tempo recebido do HTML:' + data);
    slaveCmd = data[0]
    slaveOut = data[1]
    slaveState = data[2]

    mensagem = ':'+slaveAdr+slaveCmd+slaveOut+slaveState;
    lrc = LRC(mensagem)
    //mensagem = ':'+slaveAdr+slaveCmd+slaveOut+slaveState+lrc;
    console.log("Mensagem:" + mensagem);
    sPort.write(mensagem);
  });
})

function LRC(str) 
{
  var bytes;
  var aux = [];
  var lrc = 0;

  /* ----- Transformando em hexadecimal ----- */
  for (var i = 1; i < str.length; i+=2) 
  { 
    if (str[i] > '9' && str[i+1] > '9')
      bytes = (Number(str.charCodeAt(i)) - '55')*16 + (Number(str.charCodeAt(i+1)) - '55');
    
    else if (str[i] > '9')
      bytes = (Number(str.charCodeAt(i)) - '55')*16 + (Number(str.charCodeAt(i+1)) - '48');

    else if (str[i+1] > '9')
      bytes = (Number(str.charCodeAt(i)) - '48')*16 + (Number(str.charCodeAt(i+1)) - '55');
    
    else
      bytes = (Number(str.charCodeAt(i)) - '48')*16 + (Number(str.charCodeAt(i+1)) - '48');
    
    aux.push(bytes);
  }

  for (var i = 0; i < (aux.length); i++)
  {

    if((lrc + aux[i]) & 0xFF)
      lrc += aux[i];

  }
  lrc = ((lrc^0xFF) + 1) & 0xFF;

  lrc = lrc.toString(16);
  lrc+="";
  lrc = lrc.toUpperCase();

  return lrc;
}

/*****   Porta Serial *****/
const SerialPort = require('serialport');
const { emit } = require('process');
const { Socket } = require('dgram');
const Readline = SerialPort.parsers.Readline;
const sPort = new SerialPort('COM5', {
  baudRate: 9600
})
const parser = new Readline();
sPort.pipe(parser);

var slaveAdr = '03';
var slaveCmd = '05';
var slaveOut = '01';
var slaveState = '0000';
var mensagem = ':' + slaveAdr + slaveCmd + slaveOut + slaveState;

sPort.open(function (err) {
  if(err) {
      console.log(err.message)
  }
  console.log('Porta Serial Aberta')
})

parser.on('data', (data) => { // ESCUTA A SERIAL E DECODIFICA
  console.log(data);

  //decodificacao
  if(data[0]==":"&&data[1]=="1"){
    
    switch(data[2]){
      case '1':
          //porta socket.emit("ResSenha", true);
            switch(data[4]){
              case '3':
                var msg = data[5]+data[6]+data[7]+data[8];
                  if(data[5]=='F'&&data[6]=='F'&&data[7]=='F'&&data[8]=='F'){
                    //emit
                    socket.emit("statePorta","Porta Aberta");
                  }
                  else if(data[5]=='0'&&data[6]=='0'&&data[7]=='0'&&data[8]=='0'){
                    socket.emit("statePorta","Porta Fechada");
                  }
                  break;
              case '2':
                  break;
            }
          break;
      case '2':
          //sala
          switch(data[4]){
            case '3':
               //state ar C
              if(data[5]=='F'&&data[6]=='F'&&data[7]=='F'&&data[8]=='F'){
                socket.emit("stateAr","Ar condicionado ligado");
              }
              else if(data[5]=='0'&&data[6]=='0'&&data[7]=='0'&&data[8]=='0'){
                socket.emit("stateAr","Ar condicionado desligado");
              }
              else {
                socket.emit("stateAr","Modo manual, temp = "+ data[7]+data[8]);
              }
                break;
            case '4':
                //state lamp 1
                var msg = data[6]+data[7]+data[8];
                socket.emit("stateLampSala",msg+"%");
                //emit
                break;
          }
          break;
      case '3':
          //janelas
          switch(data[4]){
            case '3':
              //state janela1
              var msg = data[6]+data[7]+data[8];
              //emit
              socket.emit("stateCorti1",msg+"%");
                break;
            case '4':
               //state janela2
              var msg = data[6]+data[7]+data[8];
              socket.emit("stateCorti2",msg+"%");
              //emit
                break;
            case '5':
                //catavento
              var msg = data[6]+data[7]+data[8];
                //emit
                socket.emit("stateVento",msg+"%");
                  break;
          }
          break;
      case '4':
          //quarto
          switch(data[4]){
            
            case '3':
              //lamp status
              var msg = data[6]+data[7]+data[8];
              socket.emit("stateLampQuarto",msg+"%");
                break;
            case '4':
              if(data[5]=='F'&&data[6]=='F'&&data[7]=='F'&&data[8]=='F'){
                //emit ligado
                socket.emit("stateAquece","Aquecedor ligado");
              }
              else if(data[5]=='0'&&data[6]=='0'&&data[7]=='0'&&data[8]=='0'){
                //emit desligado
                socket.emit("stateAquece","Aquecedor desligado");
              }
                break;
          }
          break;
    }
    





  }
})