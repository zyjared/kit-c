import { defineConfig } from 'vitepress'

export const shared = defineConfig({

  title: 'kit-C',

  rewrites: {
    'zh/:rest*': ':rest*',
  },

  appearance: 'dark',
  lastUpdated: true,
  cleanUrls: true,
  metaChunk: true,

  head: [
    ['link', { rel: 'apple-touch-icon', sizes: '180x180', href: '/apple-touch-icon.png' }],
    ['link', { rel: 'icon', type: 'image/png', sizes: '32x32', href: '/favicon-32x32.png' }],
    ['link', { rel: 'icon', type: 'image/png', sizes: '16x16', href: '/favicon-16x16.png' }],
    ['link', { rel: 'manifest', href: '/site.webmanifest' }],
  ],

  themeConfig: {
    logo: { src: '/apple-touch-icon.png', alt: 'kit-C' },
    socialLinks: [
      { icon: 'github', link: 'https://github.com/zyjared/kit-c' },
    ],
  },

})
