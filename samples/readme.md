Dans cet exemple, nous créons un point de départ depuis App.java pour appeler une bibliothèque qui sera créée juste après, contenant les binaires obtenus par la compilation de nos fichiers C/C++.

Il faut noter que si la bibliothèque se nomme libmabibli.jnilib, alors il faudra enlever "lib".

Ensuite, nous générons le fichier d'en-tête .h qui nous servira pour l'implémentation avec la commande :<br>
`javac -h . App.java. "` <br>
-h=création du header, .=" indique l'emplacement courant pour générer le fichier .h. La classe doit avoir une méthode native (mot clé).

Cette commande nous génère deux fichiers : App.class, contenant les binaires, et samples_App.h pour notre implémentation en C++.

Il se peut que dans le fichier samples_App.h, il ne reconnaisse pas `#include <jni.h>`, il faudra alors aller configurer l'includePath (accès rapide : mettre la souris sur le lien d'erreur > Quick fix > "modifier les paramètres includePath").

Nous cherchons le paramètre "Inclure le chemin". Sur une nouvelle ligne, nous mettons le chemin absolu vers jni.h, qui se trouve normalement dans le dossier include du dossier d'installation de Java. <br>
Exemple de chemin (MacOS) : /opt/homebrew/Cellar/openjdk/21.0.2/include.

Ensuite, nous allons créer un fichier nommé Information.cpp et y placer notre implémentation de la méthode native. Il ne faut pas oublier d'inclure notre .h généré.

Après l'implémentation des deux méthodes natives, nous lançons la commande : <br>
`g++ -I"$JAVA_HOME/include" -o libinformation.jnilib -shared Information.cpp` <br>
`g++ -arch x86_64 -I"$JAVA_HOME/include" -o libhello.dylib -shared Hello.cpp`(MacOS en cas d'erreur d'architecture),<br>
afin de créer la bibliothèque qui sera utilisée par App.java.

À noter que le nom de la bibliothèque doit commencer par "lib", et l'extension .jnilib peut être utilisée pour les trois plates-formes (Windows/MacOS/Linux) (source : https://commentouvrir.com/extension/jnilib).

Après la génération de la bibliothèque, il nous suffira de lancer la commande :<br>
`java -Djava.library.path=. App.java` afin de voir le résultat.

Résultat :
Java_samples_App_printCalcul
Java_samples_App_printName
Name: Simpson
Resultat du calcul : 5
Nom : Monsieur Simpson

