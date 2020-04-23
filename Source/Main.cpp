/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "LookAndFeel.h"
#include "SceneComponent.h"

//==============================================================================
class ConnectedPianistApplication  : public JUCEApplication
{
public:
    //==============================================================================
    ConnectedPianistApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }
    TooltipWindow tooltipWindow{nullptr, 1500};
    ::LookAndFeel lookAndFeel;

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        // This method is where you should put your application's initialisation code..

#if TARGET_OS_IPHONE
		Desktop::getInstance().setGlobalScaleFactor(1.2);
		CreateSharedDocumenstDirectory();
#endif
		Desktop::getInstance().setDefaultLookAndFeel(&lookAndFeel);
        mainWindow.reset(new MainWindow (getApplicationName()));
#if TARGET_OS_IPHONE
		mainWindow->setFullScreen(true);
#endif
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

	void CreateSharedDocumenstDirectory()
	{
		// Create app Documents directory, for use in "Files" app
		File docPath = File::getSpecialLocation(File::userDocumentsDirectory);
		DirectoryIterator iter(docPath, false);
		if (!iter.next())
		{
			File docFlag = docPath.getChildFile("Put your midi files here");
			std::unique_ptr<FileOutputStream> outp(docFlag.createOutputStream());
		}
	}

    class ConFileLogger : public FileLogger
    {
    public:
    	ConFileLogger() : FileLogger(getSystemLogFileFolder()
    	#ifdef WIN32
    		.getChildFile("ConPianist")
		#endif
    		.getChildFile("ConPianist.log"), String("ConPianist ") +
    		JUCEApplication::getInstance()->getApplicationVersion()) {}
	protected:
    	void logMessage(const String& message) override
    	{
			Time time = Time::getCurrentTime();
			String timestr = time.formatted("%Y-%m-%d %H:%M:%S.") + String(time.getMilliseconds()).paddedLeft('0', 3);
			String text(timestr + " " + message);
			FileLogger::logMessage(text);
		}
	};

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow (String name)  : DocumentWindow (name,
                                                    Desktop::getInstance().getDefaultLookAndFeel()
                                                                          .findColour (ResizableWindow::backgroundColourId),
                                                    DocumentWindow::allButtons)
        {
			settings.Load();

			if (settings.logging)
			{
				logger.reset(new ConFileLogger());
				Logger::setCurrentLogger(logger.get());
			}

            setUsingNativeTitleBar (true);
            setContentOwned (new SceneComponent(settings), true);
            setResizable (true, true);
            centreWithSize (getWidth(), getHeight());

#if !TARGET_OS_IPHONE
			Rectangle<int> bounds = settings.windowPos;
			if (bounds.getX() > -100 && bounds.getY() > -100 &&
				bounds.getWidth() > 200 && bounds.getHeight() > 100)
			{
				setBounds(bounds);
			}
#endif

            setVisible (true);
        }

		~MainWindow()
		{
			settings.windowPos = getBounds();
			settings.Save();
			Logger::writeToLog("Application ended gracefully");
			Logger::setCurrentLogger(nullptr);
		}

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
        Settings settings;
    	std::unique_ptr<FileLogger> logger;
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (ConnectedPianistApplication)
