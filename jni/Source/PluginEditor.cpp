/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/


#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <jni.h>

using namespace juce;

class CustomPluginListComponent final : public PluginListComponent
{
public:
    CustomPluginListComponent (AudioPluginFormatManager& manager,
                               KnownPluginList& listToRepresent,
                               const File& pedal,
                               PropertiesFile* props,
                               bool async)
        : PluginListComponent (manager, listToRepresent, pedal, props, async)
    {



    }

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomPluginListComponent)
};

//==============================================================================
SimpleEQAudioProcessorEditor::SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

SimpleEQAudioProcessorEditor::~SimpleEQAudioProcessorEditor()
{
}

//==============================================================================
std::string SimpleEQAudioProcessorEditor::scanPlugins() {
    // Indique de rechercher uniquement les plugins VST3
    juce::VST3PluginFormat formatToScan;

    /* Récupère la liste des dossiers où chercher des plugins VST3, ceux-ci sont définis dans
     le standard VST3 : https://steinbergmedia.github.io/vst3_dev_portal/pages/Technical+Documentation/Locations+Format/Plugin+Locations.html
     */
    juce::FileSearchPath searchPath = formatToScan.getDefaultLocationsToSearch();

    bool allowAsync = false;

    std::unique_ptr<juce::PluginDirectoryScanner> scanner;
    
    // Initialise le scanner de dossiers plugins avec nos paramètres
    scanner.reset (new juce::PluginDirectoryScanner(
        this->knownPluginList, // Liste des plugins à remplir
        formatToScan,
        searchPath,
        true, // Scan récursif
        File(), // On ne précise pas de deadMansPedalFile (dans lequel est stocké les noms des plugins qui crash)
        allowAsync
    ));

    juce::String pluginFile;
    while (scanner->scanNextFile(true, pluginFile)) {
        // Scanne tous les fichiers
    }
    
    juce::String text = "Plugins :";
    for (const auto& desc : knownPluginList.getTypes()) {
        text += desc.name + " (" + desc.pluginFormatName + ") \n";
    }
    
    return text.toStdString();
}

void SimpleEQAudioProcessorEditor::paint (juce::Graphics& g) {

    
    scanPlugins();
    
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    juce::String text = "Plugins :";
    // Parcours les plug-ins pour les ajouter à la String à afficher
    for (const auto& desc : knownPluginList.getTypes()) {
        text += desc.name + " (" + desc.pluginFormatName + ") \n";
    }

    // Affiche les noms des plugins
    g.drawFittedText(text, getLocalBounds(), juce::Justification::topLeft, 10);
}

void SimpleEQAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

JNIEXPORT jstring JNICALL Java_PluginScanner_scanFiles(JNIEnv *env, jclass obj) {
    SimpleEQAudioProcessor processor;
    juce::AudioProcessorEditor* editorGeneric = processor.createEditor();
    SimpleEQAudioProcessorEditor* editor = dynamic_cast<SimpleEQAudioProcessorEditor*>(editorGeneric);
    std::string pluginList = editor->scanPlugins();
    delete editor;
    return env->NewStringUTF(pluginList.c_str());
}
