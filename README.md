# Salvamento de dados do MQ135 no Google Sheets

###### Você pode seguir as instruções desta documentação para armazenar dados do sensor numa planilha do Google Spreadsheets. Este tutorial foi adaptado do guia ![Google-Sheets-Logging] (https://github.com/StorageB/Google-Sheets-Logging) e inclui a biblioteca ![HTTPSRedirect](https://github.com/electronicsguy/HTTPSRedirect), que é uma dependência e deve ser instalada.

<br>

## Parte 1 - Google Sheets

1. Crie uma planilha do Google Sheets, e dê um nome a ela.

2. Digite os títulos das colunas na primeira linha da planilha:

   - Célula A1: `Dia`
   - Célula B1: `Hora`
   - Célula C1: `Valor`
   - Célula D1: `Local`
   <br>

   Exemplo:
   
   ![image](https://user-images.githubusercontent.com/3741135/175699252-da06f625-6a72-442a-8af7-e7398dc644e7.png)

   
3. Da URL da planilha, copie o ID.

      ![Selection_006-3](https://user-images.githubusercontent.com/44729718/115287377-d1bad680-a115-11eb-8730-4c6ae00184a7.png)

      Por exemplo, se o endereço no navegador é:
   
         https://docs.google.com/spreadsheets/d/1sqp9hIM5VvDGEf8i9H-W1Z72lm0O5-ZxC16sMMS-cgo/edit#gid=0

      Então o ID a copiar é o que está entre `spreadsheets/d/`  e `/edit`:
   
         1sqp9hIM5VvDGEf8i9H-W1Z72lm0O5-ZxC16sMMS-cgo


4. No menu do Google Sheets, selecione `Extensions > Apps Script`
   
   ![sheets-1](https://user-images.githubusercontent.com/3741135/175667583-1ed23a37-a487-49b1-b6f3-cd1eab15d8a4.png)
   
   *Nota: O editor como padrão aparece na versão mais recente. Se por algum motivo aparecer para você a versão antiga (legacy) você deverá trocar para a mais recente clicando no botão "Use new editor" que fica no topo da página.*
   
   ![apps-script-1](https://user-images.githubusercontent.com/3741135/175667756-bc2561cb-aa03-4cdf-9da5-492ff35d24be.png)

5. Apague o código padrão que aparece no editor. Abra o arquivo GoogleScripts-example.gs aqui neste repositório, e cole o código inteiro na área de edição.

6. Na linha a seguir, no lugar de XXX, coloque o ID da sua planilha, obtido no passo 3. Clique no botão de salvar.

   
         var SS = SpreadsheetApp.openById('XXXXX');
   

   *Nota:  O ID tem que ser colocado com aspas simples, como está no código, e o script **tem que ser salvo** antes de passar para o próximo passo.*
   
7. Clique no botão azul `Deploy` no topo direito da página, e selecione `New Deployment`.
   Na janela que se abre, clique no ícone de engrenagem e escolha 'Web App'
   
   ![image](https://user-images.githubusercontent.com/3741135/175689619-eb696aea-13d6-43fc-80a0-ff509d96f97f.png)
   
   Em seguida, modifique as seguintes opções:

   - Digite uma descrição
   - Em `Execute as`, escolha `Me`
   - Em `Who has access`, escolha `Anyone` *(nota: NÃO selecione `Anyone with a Google Account` - role para encontrar `Anyone`)*

   ![image](https://user-images.githubusercontent.com/3741135/175694332-876a75e5-d1d5-4d9d-9d82-bec6c0d45569.png)
   
   Clique em `Deploy`
   
8. Clique em `Authorize access` e selecione sua conta do Google.

   ![image](https://user-images.githubusercontent.com/3741135/175695053-2790ce7b-e5c1-49d9-9a10-0707b018a621.png)
   
   Aparece uma janela de aviso dizendo "Google hasn't verified this app". Como esse app foi criado por você, não há problema, pois você mesmo é quem terá acesso às planilhas da sua conta. Selecione os pequenos links: `Advanced` > `Go to <nome do projeto> (unsafe)`
   
   
   ![image](https://user-images.githubusercontent.com/3741135/175695518-3e557cdb-1767-4aac-98c0-2125040cc74d.png)
   
   Na próxima janela, escolha `Allow`. Uma janela com o `Deployment ID` e o link do Web App aparece. Copie o `Deployment ID`, pois ele será colado no código da placa alguns passos à frente. Clique `Done`.
   

9. Na barrinha acima do editor de código, clique `Save` e depois `Run`. 

   ![image](https://user-images.githubusercontent.com/3741135/175696480-c4664f57-fa54-40c5-a182-02935f4f896e.png)

   *Nota:  Nada especial acontecerá ao clicar Run, haverá somente uma checagem de código. Mas o passo é necessário.*
 
   
## Parte 2 - Placa NodeMCU / Arduino Editor

1. Aqui neste repositório, abra o arquivo "MQ135-monitor.cpp" e copie o código completo.

2. Na interface do editor do Arduino, crie um sketch vazio, apague qualquer código padrão que apareça e cole nele o código retirado do arquivo MQ135-monitor.cpp

3. Nesse novo sketch onde colou o código, modifique:

    - O nome da sua rede de WiFi, na linha que começa com `const char* ssid;`
    - A senha da sua rede de Wifi, na linha que começa com `const char* password`
    - O ID retirado do App Scripts Editor (obtido no passo 1.8 acima)
    
    *Note:  Não esqueça de manter as aspas no código. O Deployment ID pode ser recuperado clicando em `Deploy > Manage Deployments`.*

3. Antes de testar, vamos instalar a biblioteca HTTPSRedirect, que é necessária. Para instalar, **baixe o arquivo `libraries.zip`**, incluído aqui neste repositório. 


5. Se estiver usando o Arduino Web Editor, clique em `Libraries` e clique no botão 'Import', que fica ao lado de 'Library Manager'. Então selecione o arquivo libraries.zip no seu computador e importe.

   ![image](https://user-images.githubusercontent.com/3741135/175720696-de218b31-afff-4f33-85ce-9f45d4599c96.png)

   Se estiver usando o programa instalado na sua máquina (Arduino IDE), o caminho é Sketch > Include Library > Add .ZIP library...
   
   ![image](https://user-images.githubusercontent.com/3741135/175720650-8ded44a1-bd52-46e6-ae1a-702dad2a54d8.png)


6. Caso tenha seguidos os passos até aqui, você deverá poder enviar o código do Arduino Editor para a sua placa NodeMCU. Abra o monitor serial para ver os resultados.

     

## Nota

1. Ao fazer mudanças no código do Google Scripts code, é preciso clicar em `Save`, depois `Deploy > New deployment`, clicar no ícone de editar e esolher 'New version'. Isso irá gerar um Deployment ID, que você irá colar no código do Arduino Editor.

2. Caso o envio para a placa não funcione de imediato, desconecte, recarregue a página e tente novamente. Às vezes ao enviar o código, acontecem erros de comunicação com a placa.

