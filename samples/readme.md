Dans cette exemple nous creons un point depart depuis App.java pour appelé une bibliotheque qui sera cree juste apres contenant les binaires obtenus par la compilation de nos fichier C/C++

Il faut noter que si la bibliotheque se nomme libmabibli.jnilib alors il faudra enlever "lib" 

Nous generons ensuite le header .h qui va nous servir pour l'implementation avec la commande :
`javac -h . App.java `
 -h=creation du header, .=emplacement courant pour generer le fichier .h, la class doit avoir une methode native (mot clé)

Cette commande nous genere 2 fichier :
App.class contenant les binaires et samples_App.h pour notre implementation en c++

Il se peut que dans le fichier samples_App.h, il ne reconnaissent pas `#include <jni.h>` il faudra alors aller configurer includePath (assez rapide, mettre la souris sur le lien d'erreur > Quick fix > "modifier les parametres includePath")

On cherche le parametre "Inclure le chemin" sur une nouvelle ligne on met le chemin absolu vers jni.h, 
il se trouve normalement dans le dossier include du dossier d'installation de java 
exemple de chemin (macos) : /opt/homebrew/Cellar/openjdk/21.0.2/include

Nous allons ensuite crée un fichier nommé Information.cpp et y placer notre implementation de la methode native
Il ne faut pas oublier d'inclure notre .h generer

Apres l'implementation des deux methodes natives, nous lancons la commande :
` g++ -I"$JAVA_HOME/include" -o libinformation.jnilib -shared Information.cpp`
`g++ -arch x86_64 -I"$JAVA_HOME/include" -o libhello.dylib -shared Hello.cpp (MacOS en cas d'erreur d'architecture)`
afin de cree la bibliotheque qui sera utiliser par App.java

A noter que le nom de la bibliotheque doit commencer par "lib", l'extension .jnilib peut etre utilisé pour les trois platform(Windows/MacOS/Linux) (https://commentouvrir.com/extension/jnilib)

Apres la generation de la bibliotheque il nous suffira de lancer la commande :
`java -Djava.library.path=. App.java` afin de voir le resultat.