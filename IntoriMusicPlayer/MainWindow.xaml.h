#pragma once

#include "MainWindow.g.h"

namespace winrt::IntoriMusicPlayer::implementation
{
	struct MainWindow : MainWindowT<MainWindow>
	{
		MainWindow();

		void MaterialSelectionComboBox(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);

	private:
		void InitializeSystemBackdrop();

		template<typename T, typename U>
		void SetBackdropController(U kind);

		winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration m_configurationSource{ nullptr };
		winrt::Microsoft::UI::Composition::SystemBackdrops::ISystemBackdropController m_backdropController{ nullptr };
		bool m_isMica{ true };

		void OnClose(IInspectable const&, IInspectable const&);
	};
}

namespace winrt::IntoriMusicPlayer::factory_implementation
{
	struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
	{
	};
}
