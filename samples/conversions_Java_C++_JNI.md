De manière générale, pour avoir les équivalences entre les types de Java et les types natives de C, voir : 
https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/types.html

Pour avoir les équivalences entre les types primitifs de Java, - comme byte, char, short ou void - voir le tableau suivant : 
https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/types.html#primitive_types

Pour avoir les équivalences entre les types par référence de Java, - comme class, string ou array, voir :
https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/types.html#reference_types

# Conversions

Avant de continuer, expliquons la déclaration de fonction suivante :

```cpp
JNIEXPORT void JNICALL Java_Hello_printHello(JNIEnv *env, jclass obj, jstring msg);
```

`JNIEXPORT` et `JNICALL` : Ce sont des macros spécifiques à JNI qui gèrent les spécificités de la compilation et de l’appel de la fonction sur différentes plateformes.

`void`: C'est le type de retour. Ici, la fonction ne renvoie rien.

`Java_Hello_printHello` : C'est le nom de la fonction. Il suit une convention de nommage spécifique à JNI : `Java_{package_et_nom_de_classe}_{nom_de_fonction}`

`(JNIEnv *env, jclass obj, jstring msg)` : Ce sont les paramètres de fonction avec 

`JNIEnv *env`, le pointeur vers l'environnement JNI, qui est utilisé pour accéder aux méthodes JNI.

`jclass obj`, la référence à la classe Java qui a appelé cette méthode native. Dans ce cas, c’est la classe Hello.

`jstring msg`, le paramètre que la méthode native prend. Dans ce cas, c’est une chaîne de caractères Java.

## Manipuler des chaînes de caractères en JNI

```c
const char * GetStringUTFChars(JNIEnv *env, jstring string, jboolean *isCopy);
```
Retourne un pointeur d'un tableau d'octets represantant un string encodé en UTF-8.

```c
jstring NewStringUTF(JNIEnv *env, const char *bytes);
```
Construit une chaîne `jstring` depuis un char* en UTF-8.

Ainsi, pour accéder à des chaînes de caractères Java, prenons par exemple la fonction suivante :
```cpp
JNIEXPORT void JNICALL Java_Hello_sayHello (JNIEnv *env, jclass obj, jstring jnistr) {
    // étape 1: convertir jstring en char*
    const char* cstr = env->GetStringUTFChars(jnistr,0);
    if (NULL == cstr) return NULL;

    std::cout << "Hello you said " << jnistr << std::endl;
    std::cout << "Hello you said : " << cstr << std::endl;

    env->ReleaseStringUTFChars(jnistr, cstr);   // libérer la ressource

    // étape 2: demander à l'utilisateur une string en C++
    std::string cppstr
    std::cout << "Entrer une chaîne de caractères : "
    std::cin >> cppstr

    // étape 3: convertir une string en C++ en char* puis en jstring
    return env->NewStringUTF(cppstr.c_str());
}
```

## Interfacer des objets et méthodes Java en JNI

```c
jclass GetObjectClass(JNIEnv *env, jobject obj);
```
Retourne la classe de l'objet.

```c
jfieldID GetFieldID(JNIEnv *env, jclass clazz, const char *name, const char *sig);
```
Retourne l'ID de l'attribut pour l'attribut d'instance d'une classe. L'attribut est spécifié par son nom et sa signature.

```c
jmethodID GetMethodID(JNIEnv *env, jclass clazz, const char *name, const char *sig);
```
Retourne l'ID de la méthode pour une méthode d'instance d'une classe ou d'une interface. La méthode peut-être définie dans l'une des superclasses de `clazz` et héritée de `clazz`. La méthode est définie par son nom et sa signature.

Soit la classe Java suivante :
```java
public class MyClass {
    public double value;

    public void incr() { value += 1; }

    public native void modifieValue();

    static { System.loadlibrary("MyLib"); }

    public static void main(String[] args) {
        MyClass myobj = new MyClass();

        myobj.value = 0;

        myobj.modifieValue();

        System.out.prinln("value java = " + myobj.value);
    }
}
```

On obtient :
```cpp
extern "C" JNIEXPORT void JNICALL Java_MyClass_modifieValue (JNIEnv *env, jobject, jobject obj) {
    jclass clazz = env->GetObjectClass(obj);

    jfieldID fid = env->GetFieldID(clazz, "value", "D"); // D pour double, cf Type Signatures

    jmethodID mid = env->GetMethodID(clazz, "incr", "()V"); // () car aucun paramètre pour la fonction et V pour void
    int value = env->GetIntField(obj, fid); // récupère l'attribut value de type double

    printf("value native = %lf\n", value);

    env->SetIntField(obj, fid, 10); // modifie la valeur de l'attribut value

    env->CallVoidMethod(obj, fid); // appelle la méthode incr

    value = env->GetIntField(obj, fid);

    printf("value native = %lf\n", value);
}
```

`extern "C"` : indique que le code suivant est en C, pas en C++.

`jobject` : C'est une référence à l'objet Java qui a appelé cette méthode native. Dans ce cas, c'est un objet de la classe MyClass.

`jobject obj` : C'est le paramètre que la méthode native prend. Dans ce cas, c'est un objet Java.

Et on obtient :
```
value native = 0
value native = 11
value java = 11
```


Pour rechercher d'autres fonctions, consulter : 
https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/functions.html




